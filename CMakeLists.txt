cmake_minimum_required(VERSION 3.15)

project(hacknetplusplus)

link_directories(${PROJECT_SOURCE_DIR}/ext_libs)

set(HP_LINK_LIBS lua54)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

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
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/banner
        COMMAND ${CMAKE_COMMAND} -E copy
                ${HP_LIBS_BINARIES}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

#Note: Leave ${CMAKE_DL_LIBS} last, or else it will throw a linking error.
target_link_libraries(${PROJECT_NAME} ${HP_LINK_LIBS} ${SDL2_LIBRARIES} ${CMAKE_DL_LIBS})