cmake_minimum_required(VERSION 3.15)

add_library(GRenderer SHARED graphics_render_command.cpp)

target_include_directories(GRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})