#pragma once

#include "CrossWindow/CrossWindow.h"
#include "graphics_interface.h"

namespace CW {

    class CWWindow : public Graphics::GWindow
    {
    private:
        xwin::Window fCWWindow;
        xwin::EventQueue fEventQueue;
        bool            fIsOpen;
    public:
        virtual void Create(const char* title, int width, int height) override;
        virtual void CreateContext(Graphics::GContext* context) override;
        virtual void Destroy() override;
        virtual void SwapBuffer() override;
        virtual void PollEvents() override;
        virtual bool IsOpen() override;

        virtual void MakeContextCurrent() override;

        xwin::Window* GetCWWindow();
    };

}