cmake_minimum_required(VERSION 3.6)

project(rastersoft)

#set location for compiled binaries
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

#set SDL2 variables
find_path(SDL_INCLUDE_DIR NAMES SDL.h PATHS C:/SDL2-2.0.4/include)
find_library(SDL_LIBRARY NAMES SDL2 PATHS C:/SDL2-2.0.4/lib/x64)
find_library(SDLMAIN_LIBRARY NAMES SDL2main PATHS C:/SDL2-2.0.4/lib/x64)

add_subdirectory(rastersoft)
add_subdirectory(demo)
add_subdirectory(tests)

#set Visual Studio Solution startup project
#set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})