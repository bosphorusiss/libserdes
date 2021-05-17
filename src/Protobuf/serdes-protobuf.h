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
#pragma once

#include "serdes.h"

#include <stdint.h>

/*******************************************************************************
 *
 * Serializers and deserializers
 *
 ******************************************************************************/

serdes_err_t serdes_schema_serialize_protobuf(
  serdes_schema_t *schema, const uint8_t *seralized_proto_data, int proto_size,
  uint8_t **payloadp, size_t *sizep, char *errstr, int errstr_size);

serdes_err_t serdes_deserialize_protobuf(serdes_t *serdes, void *avro,
                                         serdes_schema_t **schemap,
                                         const void *payload, size_t size,
                                         char *errstr, int errstr_size);