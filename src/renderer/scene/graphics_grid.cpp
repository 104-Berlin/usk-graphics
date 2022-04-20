#include "graphics_renderer.h"

using namespace Renderer;

RGid::RGid(unsigned int columnCount, unsigned int rowCount, float width, float height)
    : fColumnCount(columnCount), fRowCount(rowCount), fWidth(width), fHeight(height), fVertexArray(nullptr)
{
    UpdateBuffers();
}

RGid::~RGid()
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }
}

void RGid::OnRender(Graphics::GContext* context)
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

void RGid::UpdateBuffers()
{
    if (fVertexArray)
    {
        delete fVertexArray;
        fVertexArray = nullptr;
    }

    fVertexArray = Graphics::Wrapper::CreateVertexArray();

    std::vector<glm::vec3> vertices = GenerateVertices();

    Graphics::GVertexBuffer* vertexBuffer = Graphics::Wrapper::CreateVertexBuffer();
    vertexBuffer->SetData((unsigned char*) vertices.data(), vertices.size() * sizeof(glm::vec3));

    vertexBuffer->SetLayout({
        Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "Position")
    });

    Graphics::GIndexBuffer* indexBuffer = Graphics::Wrapper::CreateIndexBuffer();

    fVertexArray->AddVertexBuffer(vertexBuffer);
}

std::vector<glm::vec3> RGid::GenerateVertices()
{
    std::vector<glm::vec3> vertices;

    for (unsigned int i = 0; i < fColumnCount; i++)
    {
        vertices.push_back(glm::vec3(i * fWidth, 0.0f, 0.0f));
        vertices.push_back(glm::vec3(i * fWidth, fRowCount * fHeight, 0.0f));
    }
    for (unsigned int j = 0; j < fRowCount; j++)
    {
        vertices.push_back(glm::vec3(0.0f, j * fHeight, 0.0f));
        vertices.push_back(glm::vec3(fColumnCount * fWidth, j * fHeight, 0.0f));
    }

    return vertices;
}