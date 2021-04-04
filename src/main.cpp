#include "platform/opengl/graphics_opengl.h"
#include "platform/glfw/graphics_glfw.h"

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
    GLFW::GLFWWindow window;
    GL::GLContext mainContext;
    window.Create("My Test window", 1270, 720);
    mainContext.Init((void*) glfwGetProcAddress);

    std::vector<float> vertex_data = {
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f  
    };

    std::vector<unsigned int> index_data = {
        0, 1, 2
    };

    GL::GLShader shader;
    shader.Compile(vertexSource, fragmentSource);


    GL::GLVertexArray va;
    va.Bind();
    
    GL::GLVertexBuffer* vb = new GL::GLVertexBuffer();
    vb->SetData((unsigned char*) vertex_data.data(), vertex_data.size() * sizeof(float));
    vb->SetLayout({GBufferElement(GShaderDataType::Float3, "POSITION")});

    GL::GLIndexBuffer* ib = new GL::GLIndexBuffer();
    ib->SetData((unsigned char*) index_data.data(), index_data.size() * sizeof(unsigned int), sizeof(unsigned int));

    va.AddVertexBuffer(vb);
    va.SetIndexBuffer(ib);

    while (window.IsOpen())
    {
        window.PollEvents();

        mainContext.Clear(0, 0, 0);
        
        shader.Bind();
        va.Bind();
        G_RENDERCMD({
            glCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL));
        })


        // Swap the renderer
        Renderer::ERenderCommandQueue::Get().Execute();
        window.SwapBuffer();
    }
    window.Destroy();
}