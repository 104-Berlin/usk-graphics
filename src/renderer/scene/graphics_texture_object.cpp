#include "graphics_renderer.h"

using namespace Renderer;

RTextureObject::RTextureObject() 
    : RObject()
{
    fTexture2D = Graphics::Wrapper::CreateTexture();
    fTexture2D->SetTextureFormat(Graphics::GTextureFormat::RGBA8);
}

RTextureObject::~RTextureObject() 
{
    delete fTexture2D;
}