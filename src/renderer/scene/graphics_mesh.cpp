#include "graphics_renderer.h"

using namespace Graphics;


GMesh::GMesh() 
    : fVertexArray(nullptr), fIndexCount(0)
{
    
}

GMesh::~GMesh() 
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }
}

void GMesh::SetData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) 
{
    fVertices = vertices;
    fIndices = indices;
    fIndexCount = indices.size();

    UpdateBuffers();
}

void GMesh::BindToDraw() 
{
    if (fVertexArray)
    {
        fVertexArray->Bind();
    }
}

size_t GMesh::GetIndexCount() const
{
    return fIndexCount;
}

void GMesh::OnRender(GContext* context) 
{
    fVertexArray->Bind();

    context->DrawElements(fVertexArray->GetIndexBuffer()->GetIndexCount(), GIndexType::UNSIGNED_INT, GDrawMode::TRIANGLES);
    
    fVertexArray->Unbind();
}

void GMesh::UpdateBuffers() 
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }

    fVertexArray = Graphics::Wrapper::CreateVertexArray();

    Graphics::GVertexBuffer* vertexBuffer = Graphics::Wrapper::CreateVertexBuffer();
    vertexBuffer->SetData((unsigned char*) fVertices.data(), fVertices.size() * sizeof(Vertex));

    vertexBuffer->SetLayout({Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Position")});

    Graphics::GIndexBuffer* indexBuffer = Graphics::Wrapper::CreateIndexBuffer();
    indexBuffer->SetData((unsigned char*)fIndices.data(), fIndices.size() * sizeof(unsigned int), sizeof(unsigned int));

    fVertexArray->AddVertexBuffer(vertexBuffer);
    fVertexArray->SetIndexBuffer(indexBuffer); 
}

GLine::GLine() 
    : GMesh()
{
    fIndices = {0, 1};
    fVertices = {{{0.0f, 0.0f, 0.0f}}, {{0.0f, 0.0f, 0.0f}}};
    fIndexCount = 2;
    UpdateBuffers();
}

void GLine::SetStart(const glm::vec3& point) 
{
    fVertices[0] = {point};
    fStart = point;
    UpdateBuffers();
}

void GLine::SetEnd(const glm::vec3& point) 
{
    fVertices[1] = {point};
    fEnd = point;
    UpdateBuffers();
}