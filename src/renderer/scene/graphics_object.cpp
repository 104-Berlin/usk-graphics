#include "graphics_renderer.h"

using namespace Renderer;

RObject::RObject() 
    :   fModelMatrix(1.0),
        fPosition(),
        fScale(glm::vec3(1.0f)),
        fRotation(),
        fMatrixAutoUpdate(true),
        fParent(nullptr)
{
    
}

RObject::~RObject() 
{
    
}

const glm::vec3& RObject::GetPosition() const
{
    return fPosition;
}

const glm::vec3& RObject::GetScale() const
{
    return fScale;
}

const glm::quat& RObject::GetRotation() const
{
    return fRotation;
}

void RObject::SetPosition(const glm::vec3& value) 
{
    fPosition = value;
}

void RObject::SetScale(const glm::vec3& value) 
{
    fScale = value;
}

void RObject::SetRotation(const glm::quat& value) 
{
    fRotation = value;
}

void RObject::SetMatrixAutoUpdate(bool value) 
{
    fMatrixAutoUpdate = value;
}

bool RObject::GetMatrixAutoUpdate() const
{
    return fMatrixAutoUpdate;
}

glm::mat4 RObject::GetModelMatrix()
{
    if (fMatrixAutoUpdate)
    {
        UpdateMatrix();
    }
    return fModelMatrix;
}

void RObject::SetModelMatrix(const glm::mat4& modelMatrix) 
{
    glm::mat4 parentMat(1.0f);
    if (fParent)
    {
        parentMat = fParent->GetModelMatrix();
    }
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(GetModelMatrix() * glm::inverse(parentMat), scale, rotation, position, skew, perspective);
    SetPosition(position);
    SetScale(scale);
    SetRotation(rotation);
}

void RObject::UpdateMatrix() 
{
    glm::mat4 parentMatrix(1.0);
    if (fParent)
    {
        parentMatrix = fParent->GetModelMatrix();
    }

    glm::mat4 localMatrix(1.0);
    localMatrix *= glm::translate(glm::mat4(1.0f), fPosition);
    localMatrix *= glm::toMat4(fRotation);
    localMatrix *= glm::scale(glm::mat4(1.0f), fScale);
    localMatrix *= parentMatrix;
    fModelMatrix = localMatrix;
}

void RObject::Add(RObject* object) 
{
    fChildren.push_back(object);
    object->fParent = this;
}

void RObject::Attach(RObject* object) 
{
    glm::mat4 modelMatrix = GetModelMatrix();
    fChildren.push_back(object);
    object->fParent = this;
    SetModelMatrix(modelMatrix);
}

const std::vector<RObject*>& RObject::GetChildren() const
{
    return fChildren;
}

RObject* RObject::GetParent() const
{
    return fParent;
}

void RObject::Render(Graphics::GContext* context) 
{
    OnRender(context);
}

void RObject::RemoveChild(RObject* object) 
{
    std::vector<RObject*>::iterator it = std::find(fChildren.begin(), fChildren.end(), object);
    if (it != fChildren.end())
    {
        fChildren.erase(it);
    }
}