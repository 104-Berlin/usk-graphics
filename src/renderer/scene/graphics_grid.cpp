#include "graphics_renderer.h"

using namespace Renderer;

RGrid::RGrid(unsigned int columnCount, unsigned int rowCount, float width, float height)
    : fColumnCount(columnCount), fRowCount(rowCount), fWidth(width), fHeight(height), fVertexArray(nullptr)
{
    UpdateBuffers();
}

RGrid::~RGrid()
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }
}

void RGrid::OnRender(Graphics::GContext* context)
{
    if (!fVertexArray)
    {
        return;
    }

    fVertexArray->Bind();

    //context->DrawElements(fVertexArray->GetIndexBuffer()->GetIndexCount(), Graphics::GIndexType::UNSIGNED_INT, Graphics::GDrawMode::TRIANGLES);
    context->DrawArrays(0, (fColumnCount + fRowCount) * 2, Graphics::GDrawMode::LINES);
    
    fVertexArray->Unbind();
}

void RGrid::UpdateBuffers()
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }

    fVertexArray = Graphics::Wrapper::CreateVertexArray();

    std::vector<RMesh::Vertex> vertices = GenerateVertices();

    Graphics::GVertexBuffer* vertexBuffer = Graphics::Wrapper::CreateVertexBuffer();
    vertexBuffer->SetData((unsigned char*) vertices.data(), vertices.size() * sizeof(RMesh::Vertex));

    vertexBuffer->SetLayout({
        Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Position"),
        Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Normal")
    });

    Graphics::GIndexBuffer* indexBuffer = Graphics::Wrapper::CreateIndexBuffer();

    fVertexArray->AddVertexBuffer(vertexBuffer);
}

std::vector<RMesh::Vertex> RGrid::GenerateVertices()
{
    std::vector<RMesh::Vertex> vertices;

    for (unsigned int i = 0; i < fColumnCount; i++)
    {
        vertices.push_back(RMesh::Vertex(glm::vec3(i * fWidth, 0.0f, 0.0f), glm::vec3(0.0f)));
        vertices.push_back(RMesh::Vertex(glm::vec3(i * fWidth, fRowCount * fHeight, 0.0f), glm::vec3(0.0f)));
    }
    for (unsigned int j = 0; j < fRowCount; j++)
    {
        vertices.push_back(RMesh::Vertex(glm::vec3(0.0f, j * fHeight, 0.0f), glm::vec3(0.0f)));
        vertices.push_back(RMesh::Vertex(glm::vec3(fColumnCount * fWidth, j * fHeight, 0.0f), glm::vec3(0.0f)));
    }

    return vertices;
}