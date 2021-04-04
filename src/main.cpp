#include "platform/opengl/graphics_opengl.h"
#include "platform/glfw/graphics_glfw.h"

using namespace Graphics;

int main()
{
    GLFW::GLFWWindow window;
    GL::GLContext mainContext;
    window.Create("My Test window", 1270, 720);
    mainContext.Init((void*) glfwGetProcAddress);

    while (window.IsOpen())
    {
        mainContext.Clear();

        window.PollEvents();

        // Swap the renderer
        Renderer::ERenderCommandQueue::Get().Execute();
        window.SwapBuffer();
    }
    window.Destroy();
}