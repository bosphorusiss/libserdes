/**
 * Copyright 2015-2021 Confluent Inc.
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
#pragma once

#include "serdescpp.h"
#include "serdescpp_int.h"

#include <string>

namespace Serdes {

class SERDES_EXPORT Protobuf : public virtual Handle
{
  public:
    virtual ~Protobuf() = 0;

    /**
     * Create Protobuf serializer/deserializer
     */
    static Protobuf *create(const Conf *conf, std::string &errstr);

    /**
     * Serialize the generic Protobuf datum to output vector 'out'.
     * Returns the number of bytes written to 'out' or -1 on error (in which
     * case errstr is set).
     */
    virtual ssize_t serialize(Schema *schema,
                              const std::string &serialized_data,
                              std::vector<char> &out, std::string &errstr) = 0;

    virtual ssize_t deserialize(Schema **schemap, std::string &datump,
                                const void *payload, size_t size,
                                std::string &errstr) = 0;
};

class ProtobufImpl : virtual public Protobuf, virtual public HandleImpl
{
  public:
    ~ProtobufImpl() {}

    static Protobuf *create(const Conf *conf, std::string &errstr);

    ssize_t serialize(Schema *schema, const std::string &serialized_data,
                      std::vector<char> &out, std::string &errstr);

    ssize_t deserialize(Schema **schemap, std::string &datump,
                        const void *payload, size_t size, std::string &errstr);

    ssize_t serializer_framing_size() const
    {
        return dynamic_cast<const HandleImpl *>(this)
          ->serializer_framing_size();
    }

    ssize_t deserializer_framing_size() const
    {
        return dynamic_cast<const HandleImpl *>(this)
          ->deserializer_framing_size();
    }

    int schemas_purge(int max_age)
    {
        return dynamic_cast<HandleImpl *>(this)->schemas_purge(max_age);
    }
};
}  // namespace Serdes
