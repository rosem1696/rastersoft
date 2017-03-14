set(TESTS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#get all source and header files recursively
file(GLOB_RECURSE SRC_FILES ${TESTS_SOURCE_DIR}/*.c)
file(GLOB_RECURSE HEADER_FILES ${TESTS_INCLUDE_DIR}/*.h)

#create source groups
source_group("C Files" FILES ${SRC_FILES})
source_group("HEADER Files" FILES ${HEADER_FILES})

#create executable target
add_executable(tests ${SRC_FILES} ${HEADER_FILES})

#change target settings
target_include_directories(tests PUBLIC ${SDL_INCLUDE_DIR})
target_link_libraries(tests ${SDL_LIBRARY} ${SDLMAIN_LIBRARY} ${PROJECT_NAME})
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})