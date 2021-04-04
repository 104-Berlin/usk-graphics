cmake_minimum_required(VERSION 3.15)
project(USKGraphics)

# GLOBAL SETTINGS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


add_subdirectory(src/interface)
add_subdirectory(src/renderer)

add_subdirectory(src/platform/opengl)
add_subdirectory(src/platform/glfw)

target_link_libraries(GOpenGL GInterface)
target_link_libraries(GOpenGL GRenderer)
target_link_libraries(GGLFW GInterface)



add_executable(Main src/main.cpp)

target_link_libraries(Main GOpenGL)
target_link_libraries(Main GGLFW)