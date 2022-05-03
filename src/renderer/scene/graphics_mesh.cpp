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

    UpdateBuffers();
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

void RMesh::OnRender(Graphics::GContext* context) 
{
    if (!fVertexArray)
    {
        return;
    }
    fVertexArray->Bind();

    context->DrawElements(fVertexArray->GetIndexBuffer()->GetIndexCount(), Graphics::GIndexType::UNSIGNED_INT, Graphics::GDrawMode::TRIANGLES);
    
    fVertexArray->Unbind();
}

void RMesh::UpdateBuffers() 
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }

    fVertexArray = Graphics::Wrapper::CreateVertexArray();

    Graphics::GVertexBuffer* vertexBuffer = Graphics::Wrapper::CreateVertexBuffer();
    vertexBuffer->SetData((unsigned char*) fVertices.data(), fVertices.size() * sizeof(Vertex));

    vertexBuffer->SetLayout({
        Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Position"),
        Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Normal")
    });

    Graphics::GIndexBuffer* indexBuffer = Graphics::Wrapper::CreateIndexBuffer();
    indexBuffer->SetData((unsigned char*)fIndices.data(), fIndices.size() * sizeof(unsigned int), sizeof(unsigned int));

    fVertexArray->AddVertexBuffer(vertexBuffer);
    fVertexArray->SetIndexBuffer(indexBuffer); 
}

RTestMesh::RTestMesh()
    : fVertexArray(nullptr)
{
    
}

RTestMesh::~RTestMesh()
{
    /*for (Graphics::GVertexArray* array : fVertexArray)
    {
        delete array;
    }
    fVertexArray.clear();*/
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }
}

void RTestMesh::SetData(const std::vector<Vertex>& vertices)
{
    fVertices = vertices;

    UpdateBuffers();
}

void RTestMesh::OnRender(Graphics::GContext* context)
{
    /*if (fVertexArray.size() != fVertices.size())
    {
        return;
    }

    for (size_t i = 0; i < fVertexArray.size(); i++)
    {
        Graphics::GVertexArray* vertexArray = fVertexArray[i];
        size_t count = fVertices[i].size();

        vertexArray->Bind();


        context->DrawArrays(0, count, Graphics::GDrawMode::TRIANGLE_FAN);
        
        vertexArray->Unbind();
    }*/

    fVertexArray->Bind();
    context->DrawArrays(0, fVertices.size(), Graphics::GDrawMode::TRIANGLE_FAN);
    fVertexArray->Unbind();
}

void RTestMesh::UpdateBuffers()
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }
    fVertexArray = GetSingleBuffer(fVertices);
    /*for (Graphics::GVertexArray* array : fVertexArray)
    {
        delete array;
    }
    fVertexArray.clear();
    fVertexArray.resize(0);

    for (const std::vector<Vertex>& vertices : fVertices)
    {
        fVertexArray.push_back(GetSingleBuffer(vertices));
    }*/
}

Graphics::GVertexArray* RTestMesh::GetSingleBuffer(const std::vector<Vertex>& vertices)
{
    Graphics::GVertexArray* resultVertexArray = Graphics::Wrapper::CreateVertexArray();

    Graphics::GVertexBuffer* vertexBuffer = Graphics::Wrapper::CreateVertexBuffer();
    vertexBuffer->SetData((unsigned char*) fVertices.data(), fVertices.size() * sizeof(Vertex));

    vertexBuffer->SetLayout({
        Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Position"),
        Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Normal")
    });

    resultVertexArray->AddVertexBuffer(vertexBuffer);

    return resultVertexArray;
}