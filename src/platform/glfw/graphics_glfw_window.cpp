#include "graphics_glfw.h"

using namespace GLFW;

void GLFWWindow::Create(const char* title, int width, int height) 
{
    if (!glfwInit())
    {
        printf("Could not init glfw!");
        return;
    }

    fGLFWWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!fGLFWWindow)
    {
        printf("Could not create window!");
        return;
    }

    glfwMakeContextCurrent(fGLFWWindow);
}

void GLFWWindow::Destroy() 
{
    if (fGLFWWindow)
    {
        glfwDestroyWindow(fGLFWWindow);
        glfwTerminate();
    }
}

void GLFWWindow::SwapBuffer() 
{
    if (!fGLFWWindow)
    {
        printf("Window was not created when swapping buffers. Canceling...");
        return;
    }
    glfwSwapBuffers(fGLFWWindow);
}

void GLFWWindow::PollEvents() 
{
    glfwPollEvents();
}

bool GLFWWindow::IsOpen() 
{
    if (!fGLFWWindow)
    {
        printf("Window was not created when checking for open.");
        return false;
    }
    return !glfwWindowShouldClose(fGLFWWindow);
}

void GLFWWindow::MakeContextCurrent() 
{
    if (!fGLFWWindow)
    {
        printf("Window was not created when making context current.");
        return;
    }
    glfwMakeContextCurrent(fGLFWWindow);
}
