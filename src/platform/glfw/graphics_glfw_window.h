#pragma once

namespace GLFW {

    class GLFWWindow : public Graphics::GWindow
    {
    private:
        GLFWwindow* fGLFWWindow;
    public:
        virtual void Create(const char* title, int width, int height) override;
        virtual void Destroy() override;
        virtual void SwapBuffer() override;
        virtual void PollEvents() override;
        virtual bool IsOpen() override;

        virtual void MakeContextCurrent() override;

        GLFWwindow* GetGlfwWindow() const;
    };

}