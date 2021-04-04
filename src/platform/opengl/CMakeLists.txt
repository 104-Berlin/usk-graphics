cmake_minimum_required(VERSION 3.15)

add_library(GOpenGL STATIC  glad/src/glad.c
                            graphics_gl_error.cpp
                            graphics_gl_buffer.cpp
                            graphics_gl_shader.cpp
                            graphics_gl_context.cpp)

target_include_directories(GOpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

find_package(OpenGL REQUIRED)
target_link_libraries(GOpenGL ${OPENGL_LIBRARY})