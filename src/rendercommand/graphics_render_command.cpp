#include "graphics_render_command.h"

using namespace Renderer;


void RRenderCommandQueue::Submit(RRenderCommand *renderCommand) 
{
    fCommandQueue.push(renderCommand);    
}

void RRenderCommandQueue::Execute() 
{
    while (fCommandQueue.size() > 0)
    {
        fCommandQueue.front()->Execute();
        delete fCommandQueue.front();
        fCommandQueue.pop();
    }
}

RRenderCommandQueue& RRenderCommandQueue::Get() 
{
    static RRenderCommandQueue queue;
    return queue;   
}
