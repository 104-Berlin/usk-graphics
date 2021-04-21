cmake_minimum_required(VERSION 3.15)

add_library(GRenderer STATIC    graphics_mesh.cpp
                                graphics_camera.cpp
                                graphics_renderer_base.cpp
                                graphics_renderer_3d.cpp)

target_include_directories(GRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})