#include "graphics_renderer.h"

using namespace Renderer;


const char* renderer_2d_vertex_shader = R"(
#version 330 core

layout(location = 0) in vec3 vPosition;

uniform mat4 vp_matrix;
)";


RRenderer2D::RRenderer2D(Graphics::GContext* context) 
    : RRendererBase(context), fCurrentFrameBuffer(nullptr)
{

}

void RRenderer2D::Begin(Graphics::GFrameBuffer* frameBuffer, RCamera* camera) 
{
    fCurrentFrameBuffer = frameBuffer;

}

void RRenderer2D::End() 
{
    
}
