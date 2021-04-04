cmake_minimum_required(VERSION 3.15)

add_library(GInterface INTERFACE)
target_include_directories(GInterface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})