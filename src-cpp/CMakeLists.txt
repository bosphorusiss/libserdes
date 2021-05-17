set(TARGET_NAME "serdes-cpp")

file(GLOB CPP_SRC_FILES "Core/*.cpp")

add_library(${TARGET_NAME} SHARED ${CPP_SRC_FILES})

set(CPP_PUBLIC_HEADERS
            Core/serdescpp.h
            Core/serdescpp_int.h)
target_include_directories(
    ${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core>
)

set_property(TARGET ${TARGET_NAME} PROPERTY VERSION ${PROJECT_VERSION})

if(${COMPILE_SERIALIZER_AVRO_CPP} AND ${COMPILE_CPP_INTERFACE})
    pkg_check_modules(AVRO_CPP QUIET avro-cpp)
    target_include_directories(${TARGET_NAME} PUBLIC "Avro" ${AVRO_CPP_INCLUDE_DIRS})

    file(GLOB AVRO_CPP_INT_SRC_FILES "Avro/*.cpp")
    target_sources(${TARGET_NAME} PUBLIC ${AVRO_CPP_INT_SRC_FILES})
    target_link_libraries(${TARGET_NAME} PUBLIC avrocpp)
    set(CPP_PUBLIC_HEADERS "${CPP_PUBLIC_HEADERS};Avro/serdescpp-avro.h")
endif()

if(${COMPILE_SERIALIZER_PROTOBUF_CPP} AND ${COMPILE_CPP_INTERFACE})
    pkg_check_modules(PROTOBUF QUIET libprotobuf)
    target_include_directories(${TARGET_NAME} PUBLIC "Protobuf" ${PROTOBUF_INCLUDE_DIRS})

    file(GLOB PROTOBUF_CPP_INT_SRC_FILES "Protobuf/*.cpp")
    target_sources(${TARGET_NAME} PUBLIC ${PROTOBUF_CPP_INT_SRC_FILES})
    target_link_libraries(${TARGET_NAME} PUBLIC ${PROTOBUF_LDFLAGS})

    set(CPP_PUBLIC_HEADERS "${CPP_PUBLIC_HEADERS};Protobuf/serdescpp-protobuf.hpp")
endif()

target_link_libraries(${TARGET_NAME} PUBLIC serdes-c)

set_target_properties(${TARGET_NAME} PROPERTIES PUBLIC_HEADER "${CPP_PUBLIC_HEADERS}")
set_property(TARGET ${TARGET_NAME} PROPERTY VERSION ${PROJECT_VERSION})
include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
