cmake_minimum_required(VERSION 2.8)

project(rastersoft)

#set location for compiled binaries
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(rastersoft)
add_subdirectory(demo)
add_subdirectory(tests)

#set Visual Studio Solution startup project
#set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
