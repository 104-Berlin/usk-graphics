#include "graphics_renderer.h"

using namespace Renderer;


void ERenderCommandQueue::Submit(ERenderCommand *renderCommand) 
{
    fCommandQueue.push(renderCommand);    
}

void ERenderCommandQueue::Execute() 
{
    while (fCommandQueue.size() > 0)
    {
        fCommandQueue.front()->Execute();
        delete fCommandQueue.front();
        fCommandQueue.pop();
    }
}

ERenderCommandQueue& ERenderCommandQueue::Get() 
{
    static ERenderCommandQueue queue;
    return queue;   
}
