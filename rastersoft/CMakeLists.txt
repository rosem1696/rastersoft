set(RASTERSOFT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(RASTERSOFT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#get all source and header files recursively
file(GLOB_RECURSE SRC_FILES ${RASTERSOFT_SOURCE_DIR}/*.c)
file(GLOB_RECURSE HEADER_FILES ${RASTERSOFT_INCLUDE_DIR}/*.h)

#create source groups
source_group("C Files" FILES ${SRC_FILES})
source_group("HEADER Files" FILES ${HEADER_FILES})

#create executable target
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})

#change target settings
target_include_directories(${PROJECT_NAME} PUBLIC ${RASTERSOFT_INCLUDE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
