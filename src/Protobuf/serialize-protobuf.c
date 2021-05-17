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

#include "serdes-protobuf.h"
#include "serdes_int.h"

serdes_err_t serdes_schema_serialize_protobuf(
  serdes_schema_t *ss, const uint8_t *seralized_proto_data, int proto_size,
  uint8_t **payloadp, size_t *sizep, char *errstr, int errstr_size)
{
    uint8_t *payload;
    ssize_t of;
    size_t framing_size = serdes_serializer_framing_size(ss->ss_sd);
    size_t required_size = framing_size + proto_size;

    if (!payloadp) {
        /* Application is querying for buffer size */
        *sizep = required_size;
        return SERDES_ERR_OK;
    } else if (*payloadp) {
        /* Application provided a buffer */

        if (*sizep < required_size) {
            /* Make sure application's buffer is large enough */
            snprintf(errstr, errstr_size,
                     "Provided buffer size %zd < required "
                     "buffer size %zd",
                     *sizep, required_size);
            return SERDES_ERR_BUFFER_SIZE;
        }
        payload = *payloadp;
    } else {
        payload = malloc(required_size);
    }

    of = serdes_framing_write(ss, payload, required_size);
    if (of == -1) {
        snprintf(errstr, errstr_size, "Not enough space for framing");
        if (!*payloadp)
            free(payload);
        return SERDES_ERR_BUFFER_SIZE;
    }

    *payloadp = payload;
    *sizep = required_size;

    // fill rest with proto data
    memcpy(&(*payloadp)[framing_size], seralized_proto_data, proto_size);

    return SERDES_ERR_OK;
}
