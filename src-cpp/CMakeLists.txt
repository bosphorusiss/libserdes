set(TARGET_NAME "serdes-cpp")

file(GLOB CPP_SRC_FILES "Core/*.cpp")

add_library(${TARGET_NAME} SHARED ${CPP_SRC_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES PUBLIC_HEADER "serdescpp.h")

target_include_directories(
    ${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core>
)

if(${COMPILE_SERIALIZER_AVRO_CPP} AND ${COMPILE_CPP_INTERFACE})
    pkg_check_modules(AVRO_CPP QUIET avro-cpp)
    target_include_directories(${TARGET_NAME} PUBLIC "Avro" ${AVRO_CPP_INCLUDE_DIRS})

    file(GLOB AVRO_CPP_INT_SRC_FILES "Avro/*.cpp")
    target_sources(${TARGET_NAME} PUBLIC ${AVRO_CPP_INT_SRC_FILES})
    target_link_libraries(${TARGET_NAME} PUBLIC avrocpp)
endif()

target_link_libraries(${TARGET_NAME} PUBLIC serdes-c)

include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
