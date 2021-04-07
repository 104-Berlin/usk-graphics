add_library(GRenderCommand SHARED graphics_render_command.cpp
                                    graphics_shared_buffer.cpp)
target_compile_definitions(GRenderCommand PRIVATE GRCMD_EXPORT)
target_include_directories(GRenderCommand PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})