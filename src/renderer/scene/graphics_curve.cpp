#include "graphics_renderer.h"

using namespace Renderer;

RBezierCurve::RBezierCurve() 
    : RMesh(), fStartPos(100.0f, 100.0f, 0.0f), fEndPos(200.0f, 100.0f, 0.0f), fControll1(100.0f, 50.0f, 0.0f), fControll2(200.0f, 50.0f, 0.0f), fThickness(3.0f)
{
    RegenMesh();
}

void RBezierCurve::SetStartPos(const glm::vec3& pos) 
{
    fStartPos = pos;
    RegenMesh();
}

const glm::vec3& RBezierCurve::GetStartPos() const
{
    return fStartPos;
}

void RBezierCurve::SetEndPos(const glm::vec3& pos) 
{
    fEndPos = pos;
    RegenMesh();
}

const glm::vec3& RBezierCurve::GetEndPos() const
{
    return fEndPos;
}

void RBezierCurve::SetControll1(const glm::vec3& pos) 
{
    fControll1 = pos;
    RegenMesh();
}

const glm::vec3& RBezierCurve::GetControll2() const
{
    return fControll1;
}

void RBezierCurve::SetControll2(const glm::vec3& pos) 
{
    fControll2 = pos;
    RegenMesh();
}

const glm::vec3& RBezierCurve::GetControll1() const
{
    return fControll2;
}

void RBezierCurve::SetThickness(float thickness) 
{
    fThickness = thickness;
}

float RBezierCurve::GetThickness() const
{
    return fThickness;
}

void RBezierCurve::RegenMesh() 
{
    fVertices.clear();
    fIndices.clear();

    unsigned int indexCounter = 0;

    float halfWidth = fThickness / 2.0f;
    float step = 0.1f;
    float t = step;
    glm::vec3 currentPoint = GetCurvePoint(0.0f);
    glm::vec3 currentNormal = GetCurveNormal(0.0f);
    bool breakLoop = false;
    while (true)
    {
        if (t > 1.0f) 
        {
            t == 1.0f;
            breakLoop = true;
        }
        glm::vec3 nextPosition = GetCurvePoint(t);
        glm::vec3 nextNormal = GetCurveNormal(t);

        
        fVertices.push_back({currentPoint - (currentNormal * halfWidth)});
        fVertices.push_back({currentPoint + (currentNormal * halfWidth)});
        fVertices.push_back({nextPosition + (nextNormal * halfWidth)});
        fVertices.push_back({nextPosition - (nextNormal * halfWidth)});

        fIndices.push_back(indexCounter);
        fIndices.push_back(indexCounter + 1);
        fIndices.push_back(indexCounter + 2);
        fIndices.push_back(indexCounter + 2);
        fIndices.push_back(indexCounter + 3);
        fIndices.push_back(indexCounter);

        indexCounter += 4;

        currentPoint = nextPosition;
        currentNormal = nextNormal;
        t += step;
        if (breakLoop)
        {
            break;
        }
    }
    fIndexCount = fIndices.size();
    UpdateBuffers();
}

glm::vec3 RBezierCurve::GetCurvePoint(float t) 
{
    return  (fStartPos * (-(t*t*t) + (3*t*t) - (3*t) + 1)) +
            (fControll1 * ((3*t*t*t) - (6*t*t) + (3*t))) + 
            (fControll2 * (-(3*t*t*t) + (3*t*t))) + 
            (fEndPos * (t*t*t));
}

glm::vec3 RBezierCurve::GetCurveNormal(float t) 
{
    const glm::vec3 upVector(0.0f, 0.0f, 1.0f);
    glm::vec3 forwardVector = (fStartPos * (-(3*t*t) + (6*t) -3)) + 
                                (fControll1 * ((9*t*t) - (12*t) + 3)) + 
                                (fControll2 * (-(9*t*t) + (6*t))) + 
                                (fEndPos * (3*t*t));

    return glm::normalize(glm::cross(glm::normalize(forwardVector), upVector));
}