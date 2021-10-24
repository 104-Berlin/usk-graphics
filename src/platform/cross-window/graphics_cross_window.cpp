#include "graphics_cross_window.h"

using namespace CW;

void CWWindow::Create(const char* title, int width, int height) 
{
    fIsOpen = false;
    xwin::WindowDesc windowDesc;
    windowDesc.name = "CWWindow";
    windowDesc.title = title;
    windowDesc.visible = true;
    windowDesc.width = width;
    windowDesc.height = height;

    if (!fCWWindow.create(windowDesc, fEventQueue))
    {
        printf("Could not create window!\n");
        return;
    }
    fIsOpen = true;
}

void CWWindow::CreateContext(Graphics::GContext* context) 
{
    
}

void CWWindow::Destroy() 
{
    fCWWindow.close();
    fIsOpen = false;
}

void CWWindow::SwapBuffer() 
{
    
}

void CWWindow::PollEvents() 
{
    fEventQueue.update();

    while (!fEventQueue.empty())
    {
        const xwin::Event& event = fEventQueue.front();
        if (event.type == xwin::EventType::Close)
        {
            Destroy();
        }
        fEventQueue.pop();
    }
}

bool CWWindow::IsOpen() 
{
    return fIsOpen;
}

void CWWindow::MakeContextCurrent() 
{
    
}

xwin::Window* CWWindow::GetCWWindow()
{
    return &fCWWindow;
}
