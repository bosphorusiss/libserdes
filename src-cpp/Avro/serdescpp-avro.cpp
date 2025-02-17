/**
 * Copyright 2021 Confluent Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdio>
#include <exception>

#include <avro/Compiler.hh>
#include <avro/Encoder.hh>
#include <avro/Decoder.hh>
#include <avro/Generic.hh>
#include <avro/Specific.hh>
#include <avro/Exception.hh>

#include "serdescpp-avro.h"

namespace Serdes
{

    static void log_cb_trampoline(serdes_t *sd, int level,
                                  const char *fac,
                                  const char *buf, void *opaque)
    {
        HandleImpl *hnd = static_cast<HandleImpl *>(opaque);
        hnd->log_cb_->log_cb(hnd, level, fac, buf);
    }

    static void *schema_load_cb_trampoline(serdes_schema_t *schema,
                                           const char *definition,
                                           size_t definition_len,
                                           char *errstr, size_t errstr_size,
                                           void *opaque)
    {
        avro::ValidSchema *avro_schema = new (avro::ValidSchema);

        try
        {
            *avro_schema = avro::compileJsonSchemaFromMemory((const uint8_t *)definition,
                                                             definition_len);
        }
        catch (const avro::Exception &e)
        {
            snprintf(errstr, errstr_size, "Failed to compile JSON schema: %s",
                     e.what());
            delete avro_schema;
            return NULL;
        }

        return avro_schema;
    }

    static void schema_unload_cb_trampoline(serdes_schema_t *schema,
                                            void *schema_obj, void *opaque)
    {
        avro::ValidSchema *avro_schema = static_cast<avro::ValidSchema *>(schema_obj);
        delete avro_schema;
    }

    /**
     * Common function to create a serdes handle based on conf.
     */
    static int create_serdes(HandleImpl *hnd, const Conf *conf, std::string &errstr)
    {
        const ConfImpl *confimpl = conf ? dynamic_cast<const ConfImpl *>(conf) : NULL;
        serdes_conf_t *sconf;
        char c_errstr[256];

        if (confimpl)
        {
            sconf = serdes_conf_copy(confimpl->conf_);

            serdes_conf_set_opaque(sconf, (void *)hnd);

            if (confimpl->log_cb_)
            {
                serdes_conf_set_log_cb(sconf, log_cb_trampoline);
                hnd->log_cb_ = confimpl->log_cb_;
            }
        }
        else
        {
            sconf = serdes_conf_new(NULL, 0, NULL);
        }

        hnd->sd_ = serdes_new(sconf, c_errstr, sizeof(c_errstr));
        if (!hnd->sd_)
        {
            if (sconf)
                serdes_conf_destroy(sconf);
            errstr = c_errstr;
            return -1;
        }

        return 0;
    }

    Serdes::Avro::~Avro()
    {
    }

    Avro *Avro::create(const Conf *conf, std::string &errstr)
    {
        AvroImpl *avimpl = new AvroImpl();

        if (Serdes::create_serdes(avimpl, conf, errstr) == -1)
        {
            delete avimpl;
            return NULL;
        }

        return avimpl;
    }

    ssize_t AvroImpl::serialize(Schema *schema, const avro::GenericDatum *datum,
                                std::vector<char> &out, std::string &errstr)
    {
        auto avro_schema = schema->object();

        /* Binary encoded output stream */
        auto bin_os = avro::memoryOutputStream();
        /* Avro binary encoder */
        auto bin_encoder = avro::validatingEncoder(*reinterpret_cast<avro::ValidSchema*>(avro_schema),
                                                   avro::binaryEncoder());

        try
        {
            /* Encode Avro datum to Avro binary format */
            bin_encoder->init(*bin_os.get());
            avro::encode(*bin_encoder, *datum);
            bin_encoder->flush();
        }
        catch (const avro::Exception &e)
        {
            errstr = std::string("Avro serialization failed: ") + e.what();
            return -1;
        }

        /* Extract written bytes. */
        auto encoded = avro::snapshot(*bin_os.get());

        /* Write framing */
        schema->framing_write(out);

        /* Write binary encoded Avro to output vector */
        out.insert(out.end(), encoded->begin(), encoded->end());

        return out.size();
    }

    ssize_t AvroImpl::deserialize(Schema **schemap, avro::GenericDatum **datump,
                                  const void *payload, size_t size,
                                  std::string &errstr)
    {
        serdes_schema_t *ss;

        /* Read framing */
        char c_errstr[256];
        ssize_t r = serdes_framing_read(sd_, &payload, &size, &ss,
                                        c_errstr, sizeof(c_errstr));
        if (r == -1)
        {
            errstr = c_errstr;
            return -1;
        }
        else if (r == 0 && !*schemap)
        {
            errstr = "Unable to decode payload: No framing and no schema specified";
            return -1;
        }

        Schema *schema = *schemap;
        if (!schema)
        {
            schema = Serdes::Schema::get(dynamic_cast<HandleImpl *>(this),
                                         serdes_schema_id(ss), errstr);
            if (!schema)
                return -1;
        }

        auto *avro_schema = reinterpret_cast<avro::ValidSchema*>(schema->object());

        /* Binary input stream */
        auto bin_is =
            avro::memoryInputStream((const uint8_t *)payload, size);

        /* Binary Avro decoder */
        avro::DecoderPtr bin_decoder = avro::validatingDecoder(*avro_schema,
                                                               avro::binaryDecoder());

        avro::GenericDatum *datum = new avro::GenericDatum(*avro_schema);

        try
        {
            /* Decode binary to Avro datum */
            bin_decoder->init(*bin_is);
            avro::decode(*bin_decoder, *datum);
        }
        catch (const avro::Exception &e)
        {
            errstr = std::string("Avro deserialization failed: ") + e.what();
            delete datum;
            return -1;
        }

        *schemap = schema;
        *datump = datum;
        return 0;
    }
}