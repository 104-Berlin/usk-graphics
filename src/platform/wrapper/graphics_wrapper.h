#pragma once

#include "graphics_interface.h"
#include "graphics_renderer.h"
#include "imgui.h"

#ifdef G_WIN
    #ifdef G_EXPORT_WRAPPER
        #define G_API __declspec(dllexport)
    #else
        #define G_API __declspec(dllimport)
    #endif
#else
    #define G_API
#endif

namespace Graphics {
    namespace Wrapper {
        G_API void RunApplicationLoop(void(*OnInit)(GContext* context), void(*RenderCallback)(), void(*RenderImGui)());

        G_API GVertexArray* CreateVertexArray();
        G_API GVertexBuffer* CreateVertexBuffer();
        G_API GIndexBuffer* CreateIndexBuffer();
        G_API GFrameBuffer* CreateFrameBuffer(unsigned int width = 0, unsigned int height = 0, GFrameBufferFormat format = GFrameBufferFormat::RGBA8);
        G_API GShader* CreateShader();


        /**
         * Create Default Shaders
         */
        G_API Renderer::RRenderer3D Create3DRenderer(GContext* context);
    }
}