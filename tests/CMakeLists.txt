find_package(GTest REQUIRED)
pkg_check_modules(RDKAFKAPP REQUIRED rdkafka++)
find_package(Protobuf REQUIRED)

set(TEST_TARGET "test_libserdes")

set(
    SOURCES_TEST
        test_main.cpp
        test_kafka_proto.cpp
        sample.pb.cc
)

add_executable(${TEST_TARGET} ${SOURCES_TEST})

target_include_directories(${TEST_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(${TEST_TARGET}
    PRIVATE
        pthread
        ${GTEST_LIBRARIES}
        serdes-cpp
        ${RDKAFKAPP_LDFLAGS}
        ${Protobuf_LIBRARIES}
)
