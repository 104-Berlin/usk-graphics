#include "graphics_renderer.h"

using namespace Renderer;

RRendererBase::RRendererBase(Graphics::GContext* context) 
    : fContext(context)
{
    if (!context)
    {
        printf("Cant Create Renderer with undefined context!");
    }
}