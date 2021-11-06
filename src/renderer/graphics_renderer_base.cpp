#include "graphics_renderer.h"

#define NANOSVG_IMPLEMENTATION	// Expands implementation
#include "../../deps/nanosvg/src/nanosvg.h"


using namespace Renderer;

RRendererBase::RRendererBase(Graphics::GContext* context) 
    : fContext(context)
{
    if (!context)
    {
        printf("Cant Create Renderer with undefined context!");
    }
}