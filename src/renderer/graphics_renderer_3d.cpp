#include "graphics_renderer.h"

using namespace Renderer;


RRenderer3D::RRenderer3D(Graphics::GContext* context) 
    : RRendererBase(context), fCurrentFrameBuffer(nullptr), fDefaultShader(Graphics::Wrapper::GetDefault3DShader())
{
}

void RRenderer3D::Begin(Graphics::GFrameBuffer* frameBuffer) 
{
    fCurrentFrameBuffer = frameBuffer;
    frameBuffer->Bind();
    fContext->Clear();
}

void RRenderer3D::Submit(RMesh* mesh) 
{
    if (!fDefaultShader)
    {
        printf("Not shader found to render vertexarray!\n");
        return;
    }

    fDefaultShader->Bind();
    mesh->BindToDraw();

    fContext->DrawElements(mesh->GetIndexCount(), Graphics::GIndexType::UNSIGNED_INT, Graphics::GDrawMode::TRIANGLES);
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
    fCurrentFrameBuffer->Unbind();
    fCurrentFrameBuffer = nullptr;
}