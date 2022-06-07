#include "graphics_renderer.h"

using namespace Renderer;

RLine::RLine() 
    : RMesh(), fStart(), fEnd(), fThickness(2.0f)
{
    RegenVertices();
}

void RLine::SetThickness(float thickness) 
{
    fThickness = thickness;
    RegenVertices();
}

float RLine::GetThickness() const
{
    return fThickness;
}

void RLine::SetStart(const glm::vec3& point) 
{
    fStart = point;
    RegenVertices();
}

const glm::vec3& RLine::GetStart() const
{
    return fStart;
}

void RLine::SetEnd(const glm::vec3& point) 
{
    fEnd = point;
    RegenVertices();
}

const glm::vec3& RLine::GetEnd() const
{
    return fEnd;
}

void RLine::RegenVertices() 
{
    static const glm::vec3 upVector = glm::vec3(0.0f, 0.0f, 1.0f);

    float halfWidth = fThickness / 2.0f;

    glm::vec3 direction = glm::normalize(fStart - fEnd);
    glm::vec3 offsetVector = glm::normalize(glm::cross(direction, upVector));

    fMeshData.Vertices.clear();
    fMeshData.Indices.clear();
    fMeshData.Vertices.push_back({fStart - (offsetVector * halfWidth)});
    fMeshData.Vertices.push_back({fStart + (offsetVector * halfWidth)});
    fMeshData.Vertices.push_back({fEnd + (offsetVector * halfWidth)});
    fMeshData.Vertices.push_back({fEnd - (offsetVector * halfWidth)});
    
    fMeshData.Indices = {
        0, 1, 2,
        2, 3, 0
    };

    UpdateBuffers();
}