#include "platform/opengl/graphics_opengl.h"
#include "platform/glfw/graphics_glfw.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

using namespace Graphics;

const char* vertexSource = R"(
#version 330 core

layout(location = 0) in vec3 vPosition;

void main()
{
    gl_Position = vec4(vPosition, 1.0);
}
)";

const char* fragmentSource = R"(
#version 330 core

layout(location = 0) out vec4 fColor;

void main()
{
    fColor = vec4(1, 0, 0, 1);
}
)";

int main()
{
    GLFW::GLFWWindow* window = new GLFW::GLFWWindow();
    GL::GLContext mainContext;
    window->Create("My Test window", 1270, 720);
    mainContext.Init((void*) glfwGetProcAddress);


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    G_RENDERCMD1(window, {
        ImGui_ImplGlfw_InitForOpenGL(window->GetGlfwWindow(), true);
        ImGui_ImplOpenGL3_Init();
    })


    while (window->IsOpen())
    {
        window->PollEvents();

        

        G_RENDERCMD1(window, {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("HEllo ImGui");

            ImGui::End();

            ImGui::Render();
            int display_w;
            int display_h;
            glfwGetFramebufferSize(window->GetGlfwWindow(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        })


        // Swap the renderer
        Renderer::ERenderCommandQueue::Get().Execute();
        window->SwapBuffer();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window->Destroy();
    delete window;
}