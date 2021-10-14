cmake_minimum_required(VERSION 3.15)

add_library(GRenderer STATIC    graphics_camera.cpp
                                graphics_renderer_base.cpp
                                graphics_renderer_3d.cpp
                                scene/graphics_object.cpp
                                scene/graphics_mesh.cpp
                                scene/graphics_texture_object.cpp
                                scene/graphics_line.cpp
                                scene/graphics_curve.cpp
                                scene/graphics_scene.cpp)

target_include_directories(GRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})