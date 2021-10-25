#include "graphics_glfw.h"

using namespace GLFW;

void GLFWWindow::Create(const char* title, int width, int height) 
{
    if (!glfwInit())
    {
        printf("Could not init glfw!");
        return;
    }

#ifdef G_MAC
    // GL 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    fGLFWWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!fGLFWWindow)
    {
        printf("Could not create window!");
        return;
    }

    MakeContextCurrent();
}

void GLFWWindow::CreateContext(Graphics::GContext* context) 
{
    if (context)
    {
        context->Init((void*)glfwGetProcAddress);
    }
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

GLFWwindow* GLFWWindow::GetGlfwWindow() const
{
    return fGLFWWindow;
}
