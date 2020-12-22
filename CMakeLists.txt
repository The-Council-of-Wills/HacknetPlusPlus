cmake_minimum_required(VERSION 3.15)

project(hacknetplusplus)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

link_directories(${PROJECT_SOURCE_DIR}/ext_libs)

set(HP_LINK_LIBS lua54)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

if(UNIX)
        add_library(lua54 SHARED IMPORTED)
        if(APPLE)
                set_property(TARGET lua54 PROPERTY
                        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/ext_libs/liblua5.4.0.dylib)
                set(HP_LIBS_BINARIES ${PROJECT_SOURCE_DIR}/ext_libs/liblua5.4.0.dylib)
        else()
                set (CMAKE_CXX_FLAGS -ldl)
                set_property(TARGET lua54 PROPERTY
                        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/ext_libs/liblua54.so)
                set(HP_LIBS_BINARIES ${PROJECT_SOURCE_DIR}/ext_libs/liblua54.so)
        endif()
endif()
if(WIN32)
        set(HP_LIBS_BINARIES ${PROJECT_SOURCE_DIR}/ext_libs/lua54.dll)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND UNIX)
        if(NOT APPLE)
                target_link_libraries(${PROJECT_NAME} stdc++fs)
                target_compile_definitions(${PROJECT_NAME} PUBLIC hp_experimental_filesystem)
        endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/assets
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        COMMAND ${CMAKE_COMMAND} -E copy
                ${HP_LIBS_BINARIES}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

#Note: Leave ${CMAKE_DL_LIBS} last, or else it will throw a linking error.
target_link_libraries(${PROJECT_NAME} ${HP_LINK_LIBS} SDL2::Main SDL2::TTF ${CMAKE_DL_LIBS})