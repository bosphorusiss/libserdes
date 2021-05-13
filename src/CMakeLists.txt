set(TARGET_NAME "serdes-c")

file(GLOB C_SRC_FILES "*.c")

add_library(${TARGET_NAME} SHARED ${C_SRC_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES PUBLIC_HEADER "serdes.h;serdes-common.h")

target_include_directories(
    ${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

if(${COMPILE_SERIALIZER_AVRO_C})
    pkg_check_modules(AVRO_C REQUIRED avro-c)
    target_include_directories(${TARGET_NAME} PUBLIC ${AVRO_C_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} PUBLIC ${AVRO_C_LDFLAGS})
endif()

include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})