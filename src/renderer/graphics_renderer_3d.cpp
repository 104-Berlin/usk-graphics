#include "graphics_renderer.h"

using namespace Renderer;


RRenderer3D::RRenderer3D(Graphics::GContext* context) 
    : RRendererBase(context), fCurrentFrameBuffer(nullptr), fViewProjectionMatrix(), fDefaultShader(Graphics::Wrapper::GetDefault3DShader())
{
}

void RRenderer3D::Begin(Graphics::GFrameBuffer* frameBuffer, RCamera* camera) 
{
    if (fCurrentFrameBuffer)
    {
        printf("Invalid framebuffer for rendering!");
        return;
    }

    fCurrentFrameBuffer = frameBuffer;
    fViewProjectionMatrix = camera->GetProjectionMatrix(frameBuffer->GetWidth(), frameBuffer->GetHeight()) * camera->GetViewMatrix();

    fContext->EnableDepthTest(true);

    frameBuffer->Bind();
    fContext->Clear();
}

void RRenderer3D::Submit(Graphics::GVertexArray* vertexArray, Graphics::GShader* shader) 
{
    Graphics::GShader* usedShader = shader;
    if (!usedShader)
    {
        usedShader = fDefaultShader;
    }
    if (!usedShader)
    {
        printf("Not shader found to render vertexarray!\n");
        return;
    }
    usedShader->Bind();
    vertexArray->Bind();

    fContext->DrawElements(vertexArray->GetIndexBuffer()->GetIndexCount(), vertexArray->GetIndexBuffer()->GetIndexType(), Graphics::GDrawMode::TRIANGLES);
}


void RRenderer3D::End() 
{
    fContext->EnableDepthTest(false);
    fCurrentFrameBuffer->Unbind();
    fCurrentFrameBuffer = nullptr;
}
