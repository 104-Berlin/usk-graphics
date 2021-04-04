cmake_minimum_required(VERSION 3.15)

add_library(GOpenGL SHARED  glad/src/glad.c
                            graphics_gl_error.cpp
                            graphics_gl_buffer.cpp
                            graphics_gl_context.cpp)

target_include_directories(GOpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)