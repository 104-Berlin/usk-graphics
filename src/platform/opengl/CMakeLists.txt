cmake_minimum_required(VERSION 3.15)


add_library(GOpenGL STATIC  glad/src/glad.c
                            graphics_gl_error.cpp
                            graphics_gl_buffer.cpp
                            graphics_gl_shader.cpp
                            graphics_gl_context.cpp
                            graphics_gl_texture.cpp
                            ../../../deps/imgui/backends/imgui_impl_opengl3.cpp)

target_include_directories(GOpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
target_include_directories(GOpenGL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/imgui)

find_package(OpenGL REQUIRED)
target_link_libraries(GOpenGL ${OPENGL_LIBRARY})
target_compile_definitions(GOpenGL PUBLIC G_USE_OPENGL)
target_include_directories(GOpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})