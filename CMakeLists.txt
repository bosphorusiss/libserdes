cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME "serdes")
project(${TARGET_NAME}
            VERSION 7.0
            DESCRIPTION "Libserdes is a schema-based serializer/deserializer C/C++ library"
            LANGUAGES C CXX
)

set(CMAKE_DEBUG_MESSAGES "TBD" ON)

option(COMPILE_SERIALIZER_AVRO_C "Option to enable Avro data serialization system" ON)
option(COMPILE_SERIALIZER_AVRO_CPP "Option to enable Avro data serialization system for CPP interface" ON)
option(COMPILE_CPP_INTERFACE "Option to enable CPP interface for serdes" ON)

find_package(Boost REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBJANSSON REQUIRED jansson)
pkg_check_modules(LIBCURL REQUIRED libcurl)

add_subdirectory(src)

if(${COMPILE_CPP_INTERFACE})
    add_subdirectory(src-cpp)
endif()
