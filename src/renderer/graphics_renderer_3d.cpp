#include "graphics_renderer.h"

using namespace Renderer;


RRenderer3D::RRenderer3D(Graphics::GContext* context) 
    : RRendererBase(context), fCurrentFrameBuffer(nullptr)
{
    
}

void RRenderer3D::Begin(Graphics::GFrameBuffer* frameBuffer) 
{
    fCurrentFrameBuffer = frameBuffer;
    frameBuffer->Bind();
    fContext->Clear();
}

void RRenderer3D::Submit(Graphics::GVertexArray* vertexArray, Graphics::GShader* shader) 
{
    shader->Bind();
    vertexArray->Bind();

    fContext->DrawElements(vertexArray->GetIndexBuffer()->GetIndexCount(), vertexArray->GetIndexBuffer()->GetIndexType(), Graphics::GDrawMode::TRIANGLES);
}

void RRenderer3D::End() 
{
    fCurrentFrameBuffer->Unbind();
    fCurrentFrameBuffer = nullptr;
}
