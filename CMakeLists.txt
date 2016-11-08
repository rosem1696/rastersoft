cmake_minimum_required(VERSION 3.6)

project(rastersoft C)

#set project directory variables
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)

#set sdl variables
#set(SDL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SDL2/include)
find_path(SDL_INCLUDE_DIR NAMES SDL.h PATHS ${CMAKE_SOURCE_DIR}/SDL2/include)
find_library(SDL_LIBRARY NAMES SDL2 PATHS ${CMAKE_SOURCE_DIR}/SDL2/lib/x64)
find_library(SDLMAIN_LIBRARY NAMES SDL2main PATHS ${CMAKE_SOURCE_DIR}/SDL2/lib/x64)
#get all source files recursively
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.c)

#create executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

#change target settings
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR} ${SDL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARY} ${SDLMAIN_LIBRARY})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

#set Visual Studio Solution startup project
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})