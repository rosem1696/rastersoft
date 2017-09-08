set(DEMO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(DEMO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)

#get all source and header files recursively
file(GLOB_RECURSE SRC_FILES ${DEMO_SOURCE_DIR}/*.c)
file(GLOB_RECURSE HEADER_FILES ${DEMO_INCLUDE_DIR}/*.h)

#create source groups
source_group("C Files" FILES ${SRC_FILES})
source_group("HEADER Files" FILES ${HEADER_FILES})

#create executable target
add_executable(demo ${SRC_FILES} ${HEADER_FILES})

#get rastersoft library include directories 
get_target_property(RASTERSOFT_INCLUDE_DIR ${PROJECT_NAME} INCLUDE_DIRECTORIES)

#change target settings
include_directories(demo PUBLIC ${SDL2_INCLUDE_DIR} ${DEMO_INCLUDE_DIR} ${RASTERSOFT_INCLUDE_DIR})
target_link_libraries(demo ${SDL2_LIBRARY} ${PROJECT_NAME})
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
