cmake_minimum_required(VERSION 3.6)

project(rastersoft)

#set location for compiled binaries
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

#create binary directories
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR})
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/Debug)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/Release)

add_subdirectory(rastersoft)
add_subdirectory(demo)
add_subdirectory(tests)

#set Visual Studio Solution startup project
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "demo")