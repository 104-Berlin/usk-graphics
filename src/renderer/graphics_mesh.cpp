#include "graphics_renderer.h"

using namespace Renderer;


RMesh::RMesh() 
    : fVertexArray(nullptr), fIndexCount(0)
{
    
}

RMesh::~RMesh() 
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }
}

void RMesh::SetData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) 
{
    fVertices = vertices;
    fIndices = indices;
    fIndexCount = indices.size();

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

void RMesh::BindToDraw() 
{
    if (fVertexArray)
    {
        fVertexArray->Bind();
    }
}

size_t RMesh::GetIndexCount() const
{
    return fIndexCount;
}