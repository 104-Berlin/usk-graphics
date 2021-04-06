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

struct Vertex
{
    glm::vec3 position;
};

const std::vector<Vertex> vertices = {
    {{-0.5f, 0.5f, 0.0f}},
    {{ 0.5f, 0.5f, 0.0f}},
    {{ 0.0f, -0.5f, 0.0f}},
};

const std::vector<unsigned int> indices = {
    0, 1, 2
};


int main()
{
    GLFW::GLFWWindow* window = new GLFW::GLFWWindow();
    GL::GLContext mainContext;
    window->Create("My Test window", 1270, 720);
    mainContext.Init((void*) glfwGetProcAddress);

    Renderer::RRenderer3D* renderer = new Renderer::RRenderer3D(&mainContext);

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
    ImGui_ImplGlfw_InitForOpenGL(window->GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplOpenGL3_CreateFontsTexture(); // Need this to work with my renderer



    GL::GLFrameBuffer* frameBuffer = new GL::GLFrameBuffer(1270, 720, Graphics::GFramebufferFormat::RGBA16F);

    GL::GLVertexArray* vertexArray = new GL::GLVertexArray();
    vertexArray->Bind();

    GL::GLVertexBuffer* vb = new GL::GLVertexBuffer();
    vb->SetData((unsigned char*) vertices.data(), vertices.size() * sizeof(Vertex));
    vb->SetLayout({Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "POSITION")});

    GL::GLIndexBuffer* ib = new GL::GLIndexBuffer();
    ib->SetData((unsigned char*)indices.data(), indices.size() * sizeof(unsigned int), sizeof(unsigned int));
    
    vertexArray->AddVertexBuffer(vb);
    vertexArray->SetIndexBuffer(ib);
    

    GL::GLShader* shader = new GL::GLShader();
    shader->Compile(vertexSource, fragmentSource);


    while (window->IsOpen())
    {
        window->PollEvents();

        renderer->Begin(frameBuffer);
        renderer->Submit(vertexArray, shader);
        renderer->End();



        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("Hello World");
        ImGui::Image((ImTextureID)(unsigned long)frameBuffer->GetColorAttachment(), {500, 500});
        ImGui::End();

        ImGui::Render();


        G_RENDERCMD2(window, frameBuffer, {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            
            int display_w;
            int display_h;
            glfwGetFramebufferSize(window->GetGlfwWindow(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        })


        // Swap the renderer
        Renderer::RRenderCommandQueue::Get().Execute();
        window->SwapBuffer();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete vertexArray;
    delete frameBuffer;
    delete shader;
    delete renderer;
    Renderer::RRenderCommandQueue::Get().Execute();

    window->Destroy();
    delete window;
}