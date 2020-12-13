cmake_minimum_required(VERSION 3.15)

project(hacknetplusplus)

set (CMAKE_CXX_FLAGS -ldl)

add_library(lua54 STATIC IMPORTED)

IF(UNIX)
set_property(TARGET lua54 PROPERTY
             IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/liblua54.so)
ENDIF(UNIX)
IF(WIN32)
set_property(TARGET lua54 PROPERTY
             IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/liblua54.dll)
ENDIF(WIN32)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/src/Commands/help.txt
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/help
        COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/src/banner.txt
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/banner)

target_link_libraries(hacknetplusplus lua54 ${CMAKE_DL_LIBS})