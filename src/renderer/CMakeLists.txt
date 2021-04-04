cmake_minimum_required(VERSION 3.15)

add_library(GRenderer STATIC    graphics_render_command.cpp
                                graphics_shared_buffer.cpp)

target_include_directories(GRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})