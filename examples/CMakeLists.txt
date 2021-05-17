if(${COMPILE_SERIALIZER_AVRO_CPP} AND ${COMPILE_CPP_INTERFACE})
    pkg_check_modules(RDKAFKAPP REQUIRED rdkafka++)
    add_executable(kafka-serdes-avro-console-consumer kafka-serdes-avro-console-consumer.cpp)
    add_executable(kafka-serdes-avro-console-producer kafka-serdes-avro-console-producer.cpp)
    add_executable(serdes-tool serdes-tool.cpp)

    target_link_libraries(kafka-serdes-avro-console-consumer PUBLIC serdes-cpp ${RDKAFKAPP_LDFLAGS})
    target_link_libraries(kafka-serdes-avro-console-producer PUBLIC serdes-cpp ${RDKAFKAPP_LDFLAGS})
    target_link_libraries(serdes-tool PUBLIC serdes-cpp)
endif()

if(${COMPILE_SERIALIZER_AVRO_C})
    pkg_check_modules(RDKAFKA REQUIRED rdkafka)
    add_executable(serdes-kafka-avro-client serdes-kafka-avro-client.c)

    target_link_libraries(serdes-kafka-avro-client PUBLIC serdes-c ${RDKAFKA_LDFLAGS})
endif()

if(${COMPILE_SERIALIZER_PROTOBUF_C})
    pkg_check_modules(PROTOBUF_C REQUIRED libprotobuf-c)
    pkg_check_modules(RDKAFKA REQUIRED rdkafka)

    add_executable(serdes-kafka-pb-client serdes-kafka-pb-client.c sample.pb-c.c)
    target_link_libraries(serdes-kafka-pb-client PUBLIC ${RDKAFKA_LDFLAGS}  serdes-c ${PROTOBUF_C_LDFLAGS})
endif()
