#pragma once

#include "graphics_interface.h"
#include "imgui.h"
#include "ImGuizmo.h"

#ifdef G_USE_GLFW
#include "graphics_glfw_keybinds.h"
#endif

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

        static void SetImGuiContext(ImGuiContext* context)
        {
            ImGui::SetCurrentContext(context);
        }
        G_API ImGuiContext* GetCurrentImGuiContext();
        G_API GContext* GetMainContext();

        G_API void RunApplicationLoop(std::function<void(GContext* context)> initFunction, std::function<void()> RenderCallback, std::function<void()> RenderImGui, std::function<void()> CleanUp, void(*SetImGuiContext)(ImGuiContext*));

        G_API GVertexArray* CreateVertexArray();
        G_API GVertexBuffer* CreateVertexBuffer();
        G_API GIndexBuffer* CreateIndexBuffer();
        G_API GFrameBuffer* CreateFrameBuffer(unsigned int width = 0, unsigned int height = 0, GFrameBufferFormat format = GFrameBufferFormat::RGBA8);
        G_API GShader* CreateShader();


        G_API GShader* GetDefault3DShader();

       
    }
}