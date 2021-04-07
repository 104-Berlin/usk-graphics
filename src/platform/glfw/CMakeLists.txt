cmake_minimum_required(VERSION 3.15)

add_subdirectory(glfw)


add_library(GGLFW STATIC    graphics_glfw_window.cpp
                            ../../../deps/imgui/backends/imgui_impl_glfw.cpp)
target_link_libraries(GGLFW glfw)
target_include_directories(GGLFW PUBLIC glfw/include/)
target_include_directories(GGLFW PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/imgui)
target_include_directories(GGLFW PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(GGLFW PUBLIC G_USE_GLFW)