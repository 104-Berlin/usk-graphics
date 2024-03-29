#include "graphics_renderer.h"

using namespace Renderer;

RBezierCurve::RBezierCurve()
    : fThickness(1.0f), fStepsPerCurve(12), fIsDirty(false)
{
    
}

void RBezierCurve::SetSegments(const std::vector<CurveSegment>& segments)
{
    fCurveSegments = segments;
    RegenMesh();    
}

void RBezierCurve::SetThickness(float thickness)
{
    fThickness = thickness;
}
 
float RBezierCurve::GetThickness() const
{
    return fThickness;
}

void RBezierCurve::SetSteps(int steps)
{
    fStepsPerCurve = steps;
}

int RBezierCurve::GetSteps() const
{
    return fStepsPerCurve;
}

void RBezierCurve::RegenMesh()
{
    fMeshData.Vertices.clear();
    fMeshData.Indices.clear();

    unsigned int indexCounter = 0;

    float halfWidth = fThickness / 2.0f;
    float step = 1.0f / (float)abs(fStepsPerCurve);

    for (const CurveSegment& segment : fCurveSegments)
    {
        float t = step;
        glm::vec3 currentPoint = GetCurvePoint(segment, 0.0f);
        glm::vec3 currentNormal = GetCurveNormal(segment, 0.0f);
        bool breakLoop = false;
        while (true)
        {
            if (t > 1.0f) 
            {
                t = 1.0f;
                breakLoop = true;
            }
            glm::vec3 nextPosition = GetCurvePoint(segment, t);
            glm::vec3 nextNormal = GetCurveNormal(segment, t);

            
            fMeshData.Vertices.push_back({currentPoint - (currentNormal * halfWidth)});
            fMeshData.Vertices.push_back({currentPoint + (currentNormal * halfWidth)});
            fMeshData.Vertices.push_back({nextPosition + (nextNormal * halfWidth)});
            fMeshData.Vertices.push_back({nextPosition - (nextNormal * halfWidth)});

            fMeshData.Indices.push_back(indexCounter);
            fMeshData.Indices.push_back(indexCounter + 1);
            fMeshData.Indices.push_back(indexCounter + 2);
            fMeshData.Indices.push_back(indexCounter + 2);
            fMeshData.Indices.push_back(indexCounter + 3);
            fMeshData.Indices.push_back(indexCounter);

            indexCounter += 4;

            currentPoint = nextPosition;
            currentNormal = nextNormal;
            t += step;
            if (breakLoop)
            {
                break;
            }
        }
    }

    UpdateBuffers();
}

glm::vec3 RBezierCurve::GetCurvePoint(const CurveSegment& seg, float t)
{
    return  (seg.Start * (-(t*t*t) + (3*t*t) - (3*t) + 1)) +
        (seg.Controll1 * ((3*t*t*t) - (6*t*t) + (3*t))) + 
        (seg.Controll2 * (-(3*t*t*t) + (3*t*t))) + 
        (seg.End * (t*t*t));
}

glm::vec3 RBezierCurve::GetCurveNormal(const CurveSegment& seg, float t)
{
    const glm::vec3 upVector(0.0f, 0.0f, 1.0f);
    glm::vec3 forwardVector = (seg.Start * (-(3*t*t) + (6*t) -3)) + 
                                (seg.Controll1 * ((9*t*t) - (12*t) + 3)) + 
                                (seg.Controll2 * (-(9*t*t) + (6*t))) + 
                                (seg.End * (3*t*t));

    return glm::normalize(glm::cross(glm::normalize(forwardVector), upVector));
}

RBezierCurveEdit::RBezierCurveEdit() 
    : RMesh(), fThickness(3.0f), fSteps(10.0f)
{
    fStartPosition = new RObject();
    fStartPosition->SetParent(this, false);
    fEndPosition = new RObject();
    fEndPosition->SetParent(this, false);
    fControllPoint1 = new RObject();
    fControllPoint1->SetParent(this, false);
    fControllPoint2 = new RObject();
    fControllPoint2->SetParent(this, false);

    RegenMesh();
}

RBezierCurveEdit::~RBezierCurveEdit()
{
    delete fStartPosition;
    delete fEndPosition;
    delete fControllPoint1;
    delete fControllPoint2;
}

void RBezierCurveEdit::SetStartPos(const glm::vec3& pos) 
{
    if (fStartPosition->GetPosition() == pos) { return; }
    fStartPosition->SetPosition(pos);
    RegenMesh();
}

const glm::vec3& RBezierCurveEdit::GetStartPos() const
{
    return fStartPosition->GetPosition();
}

RObject* RBezierCurveEdit::GetStartPositionObject() const
{
    return fStartPosition;
}

void RBezierCurveEdit::SetEndPos(const glm::vec3& pos) 
{
    if (fEndPosition->GetPosition() == pos) { return; }
    fEndPosition->SetPosition(pos);
    RegenMesh();
}

const glm::vec3& RBezierCurveEdit::GetEndPos() const
{
    return fEndPosition->GetPosition();
}

RObject* RBezierCurveEdit::GetEndPositionObject() const
{
    return fEndPosition;
}

void RBezierCurveEdit::SetControll1(const glm::vec3& pos) 
{
    if (fControllPoint1->GetPosition() == pos) { return; }
    fControllPoint1->SetPosition(pos);
    RegenMesh();
}

const glm::vec3& RBezierCurveEdit::GetControll1() const
{
    return fControllPoint1->GetPosition();
}

RObject* RBezierCurveEdit::GetControllPoint1Object() const
{
    return fControllPoint1;
}

void RBezierCurveEdit::SetControll2(const glm::vec3& pos) 
{
    if (fControllPoint2->GetPosition() == pos) { return; }
    fControllPoint2->SetPosition(pos);
    RegenMesh();
}

const glm::vec3& RBezierCurveEdit::GetControll2() const
{
    return fControllPoint2->GetPosition();
}

RObject* RBezierCurveEdit::GetControllPoint2Object() const
{
    return fControllPoint2;
}

void RBezierCurveEdit::SetThickness(float thickness) 
{
    if (fThickness == thickness) { return; }
    fThickness = thickness;
    RegenMesh();
}

float RBezierCurveEdit::GetThickness() const
{
    return fThickness;
}

void RBezierCurveEdit::SetSteps(int steps) 
{
    if (fSteps == steps) { return; }
    fSteps = steps;
    RegenMesh();
}

int RBezierCurveEdit::GetSteps() const
{
    return fSteps;
}

void RBezierCurveEdit::RegenMesh() 
{
    fMeshData.Vertices.clear();
    fMeshData.Indices.clear();

    unsigned int indexCounter = 0;

    float halfWidth = fThickness / 2.0f;
    float step = 1.0f / (float)abs(fSteps);
    float t = step;
    glm::vec3 currentPoint = GetCurvePoint(0.0f);
    glm::vec3 currentNormal = GetCurveNormal(0.0f);
    bool breakLoop = false;
    while (true)
    {
        if (t > 1.0f) 
        {
            t = 1.0f;
            breakLoop = true;
        }
        glm::vec3 nextPosition = GetCurvePoint(t);
        glm::vec3 nextNormal = GetCurveNormal(t);

        
        fMeshData.Vertices.push_back({currentPoint - (currentNormal * halfWidth)});
        fMeshData.Vertices.push_back({currentPoint + (currentNormal * halfWidth)});
        fMeshData.Vertices.push_back({nextPosition + (nextNormal * halfWidth)});
        fMeshData.Vertices.push_back({nextPosition - (nextNormal * halfWidth)});

        fMeshData.Indices.push_back(indexCounter);
        fMeshData.Indices.push_back(indexCounter + 1);
        fMeshData.Indices.push_back(indexCounter + 2);
        fMeshData.Indices.push_back(indexCounter + 2);
        fMeshData.Indices.push_back(indexCounter + 3);
        fMeshData.Indices.push_back(indexCounter);

        indexCounter += 4;

        currentPoint = nextPosition;
        currentNormal = nextNormal;
        t += step;
        if (breakLoop)
        {
            break;
        }
    }
    UpdateBuffers();
}

glm::vec3 RBezierCurveEdit::GetCurvePoint(float t) 
{
    return  (GetStartPos() * (-(t*t*t) + (3*t*t) - (3*t) + 1)) +
            (GetControll1() * ((3*t*t*t) - (6*t*t) + (3*t))) + 
            (GetControll2() * (-(3*t*t*t) + (3*t*t))) + 
            (GetEndPos() * (t*t*t));
}

glm::vec3 RBezierCurveEdit::GetCurveNormal(float t) 
{
    const glm::vec3 upVector(0.0f, 0.0f, 1.0f);
    glm::vec3 forwardVector = (GetStartPos() * (-(3*t*t) + (6*t) -3)) + 
                                (GetControll1() * ((9*t*t) - (12*t) + 3)) + 
                                (GetControll2() * (-(9*t*t) + (6*t))) + 
                                (GetEndPos() * (3*t*t));

    return glm::normalize(glm::cross(glm::normalize(forwardVector), upVector));
}