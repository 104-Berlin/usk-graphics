cmake_minimum_required(VERSION 3.15)
project(USKGraphics)

# GLOBAL SETTINGS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} STREQUAL "")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()
if (${CMAKE_LIBRARY_OUTPUT_DIRECTORY} STREQUAL "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()
if (${CMAKE_RUNTIME_OUTPUT_DIRECTORY} STREQUAL "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()



if(APPLE)
add_compile_definitions(G_MAC)
elseif(WIN32)
add_compile_definitions(G_WIN)
else()
add_compile_definitions(G_UNI)
endif()


add_library(ImGui STATIC    deps/imgui/imgui.cpp
                            deps/imgui/imgui_demo.cpp
                            deps/imgui/imgui_draw.cpp
                            deps/imgui/imgui_widgets.cpp
                            deps/imgui/imgui_tables.cpp)

target_include_directories(ImGui PUBLIC deps/imgui)



add_subdirectory(deps/glm)
add_subdirectory(src/interface)

target_include_directories(GInterface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm)

add_subdirectory(src/renderer)

add_subdirectory(src/platform/opengl)
add_subdirectory(src/platform/glfw)


target_link_libraries(GRenderer GInterface)
target_link_libraries(GRenderer ImGui)

target_link_libraries(GOpenGL GInterface)
target_link_libraries(GOpenGL GRenderer)
target_link_libraries(GGLFW GInterface)



add_executable(Main     src/main.cpp
                        deps/imgui/backends/imgui_impl_glfw.cpp
                        deps/imgui/backends/imgui_impl_opengl3.cpp)

target_link_libraries(Main GOpenGL)
target_link_libraries(Main GGLFW)
target_link_libraries(Main ImGui)
