set(TARGET_NAME "serdes-c")

file(GLOB C_SRC_FILES "Core/*.c")

add_library(${TARGET_NAME} SHARED ${C_SRC_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES PUBLIC_HEADER "serdes.h;serdes-common.h")

target_include_directories(
    ${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core>
)

target_link_libraries(${TARGET_NAME} PRIVATE ${LIBCURL_LDFLAGS})

if(${COMPILE_SERIALIZER_AVRO_C})
    pkg_check_modules(AVRO_C REQUIRED avro-c)
    target_include_directories(${TARGET_NAME} PUBLIC "Avro" ${AVRO_C_INCLUDE_DIRS})

    file(GLOB AVRO_INT_SRC_FILES "Avro/*.c")
    target_sources(${TARGET_NAME} PUBLIC ${AVRO_INT_SRC_FILES})
    target_link_libraries(${TARGET_NAME} PUBLIC ${AVRO_C_LDFLAGS})
endif()

include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})