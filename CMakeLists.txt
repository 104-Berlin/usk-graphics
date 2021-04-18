cmake_minimum_required(VERSION 3.15)
project(USKGraphics)

# GLOBAL SETTINGS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()
if (NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()
if (NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
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
                            deps/imgui/imgui_tables.cpp
                            deps/imguizmo/ImGuizmo.cpp
                            deps/imguizmo/ImCurveEdit.cpp
                            deps/imguizmo/ImGradient.cpp
                            deps/imguizmo/ImSequencer.cpp)

                            
target_include_directories(ImGui PUBLIC deps/imgui
                                        deps/imguizmo)
                            
add_executable(ImGuizmoExmaple      deps/imguizmo/ImGuizmo.cpp
                                    deps/imguizmo/ImCurveEdit.cpp
                                    deps/imguizmo/ImGradient.cpp
                                    deps/imguizmo/ImSequencer.cpp
                                    deps/imguizmo/example/imgui.cpp
                                    deps/imguizmo/example/imgui_widgets.cpp
                                    deps/imguizmo/example/imgui_draw.cpp
                                    deps/imguizmo/example/main.cpp)
target_include_directories(ImGuizmoExmaple PRIVATE  deps/imguizmo
                                                    deps/imguizmo/example)


add_subdirectory(deps/glm)
add_subdirectory(src/interface)

target_include_directories(GInterface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm)

target_link_libraries(GInterface INTERFACE glm)

add_subdirectory(src/renderer)
add_subdirectory(src/rendercommand)

add_subdirectory(src/platform/opengl)
add_subdirectory(src/platform/glfw)

add_subdirectory(src/platform/wrapper)
target_link_libraries(GRenderer GInterface)
target_link_libraries(GRenderer GRenderCommand)
target_link_libraries(GRenderer GPlatformWrapper)

target_link_libraries(GPlatformWrapper GOpenGL)
target_link_libraries(GPlatformWrapper GGLFW)
target_link_libraries(GPlatformWrapper ImGui)



target_link_libraries(GOpenGL GInterface)
target_link_libraries(GOpenGL GRenderCommand)
target_link_libraries(GGLFW GInterface)



add_executable(Main     src/main.cpp)

target_link_libraries(Main GPlatformWrapper)
target_link_libraries(Main GRenderer)
