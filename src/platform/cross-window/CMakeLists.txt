cmake_minimum_required(VERSION 3.15)

add_subdirectory(cross-window)


add_library(GCrossWindow STATIC    graphics_cross_window.cpp)
target_link_libraries(GCrossWindow CrossWindow)
target_include_directories(GCrossWindow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/imgui)
target_include_directories(GCrossWindow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(GCrossWindow PUBLIC G_USE_CROSS_WINDOW)