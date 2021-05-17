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

#include "serdescpp-protobuf.hpp"

#include <cstdio>
#include <exception>

namespace Serdes {

static void log_cb_trampoline(serdes_t *sd, int level, const char *fac,
                              const char *buf, void *opaque)
{
    HandleImpl *hnd = static_cast<HandleImpl *>(opaque);
    hnd->log_cb_->log_cb(hnd, level, fac, buf);
}

static void *schema_load_cb_trampoline(serdes_schema_t *schema,
                                       const char *definition,
                                       size_t definition_len, char *errstr,
                                       size_t errstr_size, void *opaque)
{}

static void schema_unload_cb_trampoline(serdes_schema_t *schema,
                                        void *schema_obj, void *opaque)
{}

/**
 * Common function to create a serdes handle based on conf.
 */
static int create_serdes(HandleImpl *hnd, const Conf *conf, std::string &errstr)
{
    const ConfImpl *confimpl =
      conf ? dynamic_cast<const ConfImpl *>(conf) : NULL;
    serdes_conf_t *sconf;
    char c_errstr[256];

    if (confimpl) {
        sconf = serdes_conf_copy(confimpl->conf_);

        serdes_conf_set_opaque(sconf, (void *)hnd);

        if (confimpl->log_cb_) {
            serdes_conf_set_log_cb(sconf, log_cb_trampoline);
            hnd->log_cb_ = confimpl->log_cb_;
        }
    } else {
        sconf = serdes_conf_new(NULL, 0, NULL);
    }

    hnd->sd_ = serdes_new(sconf, c_errstr, sizeof(c_errstr));
    if (!hnd->sd_) {
        if (sconf)
            serdes_conf_destroy(sconf);
        errstr = c_errstr;
        return -1;
    }

    return 0;
}

Serdes::Protobuf::~Protobuf() {}

Protobuf *Protobuf::create(const Conf *conf, std::string &errstr)
{
    ProtobufImpl *protoimpl = new ProtobufImpl();

    if (Serdes::create_serdes(protoimpl, conf, errstr) == -1) {
        delete protoimpl;
        return NULL;
    }

    return protoimpl;
}

ssize_t ProtobufImpl::serialize(Schema *schema,
                                const std::string &serializedData,
                                std::vector<char> &out, std::string &errstr)
{

    /* Write framing */
    schema->framing_write(out);

    /* Write Message Index = 0 */
    out.insert(out.end(), 0);

    /* Write binary encoded Avro to output vector */
    out.insert(out.end(), serializedData.begin(), serializedData.end());

    return out.size();
}

ssize_t ProtobufImpl::deserialize(Schema **schemap, std::string &serializedData,
                                  const void *payload, size_t size,
                                  std::string &errstr)
{
    serdes_schema_t *ss;

    /* Read framing */
    char c_errstr[256];
    ssize_t r = serdes_framing_read(sd_, &payload, &size, &ss, c_errstr,
                                    sizeof(c_errstr));
    if (r == -1) {
        errstr = c_errstr;
        return -1;
    } else if (r == 0 && !*schemap) {
        errstr = "Unable to decode payload: No framing and no schema specified";
        return -1;
    }

    Schema *schema = *schemap;
    if (!schema) {
        schema = Serdes::Schema::get(dynamic_cast<HandleImpl *>(this),
                                     serdes_schema_id(ss), errstr);
        if (!schema)
            return -1;
    }

    *schemap = schema;

    // Drop Message write index because it's 0 in our cast and return rest
    serializedData =
      std::string(&(reinterpret_cast<const char *>(payload))[1], size - 1);
    return 0;
}
}  // namespace Serdes