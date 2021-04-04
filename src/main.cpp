#include "platform/glfw/graphics_glfw.h"
#include "platform/opengl/graphics_opengl.h"

using namespace Graphics;

int main()
{
    GLFW::GLFWWindow window;
    window.Create("My Test window", 1270, 720);
    while (window.IsOpen())
    {
        window.PollEvents();

        window.SwapBuffer();
    }
    window.Destroy();
}