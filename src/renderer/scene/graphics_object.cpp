#include "graphics_renderer.h"

using namespace Graphics;

GObject::GObject() 
    :   fModelMatrix(),
        fPosition(),
        fScale(glm::vec3(1.0f)),
        fRotation(),
        fMatrixAutoUpdate(true),
        fParent(nullptr)
{
    
}

GObject::~GObject() 
{
    
}

const glm::vec3& GObject::GetPosition() const
{
    return fPosition;
}

const glm::vec3& GObject::GetScale() const
{
    return fScale;
}

const glm::quat& GObject::GetRotation() const
{
    return fRotation;
}

void GObject::SetPosition(const glm::vec3& value) 
{
    fPosition = value;
}

void GObject::SetScale(const glm::vec3& value) 
{
    fScale = value;
}

void GObject::SetRotation(const glm::quat& value) 
{
    fRotation = value;
}

void GObject::SetMatrixAutoUpdate(bool value) 
{
    fMatrixAutoUpdate = value;
}

bool GObject::GetMatrixAutoUpdate() const
{
    return fMatrixAutoUpdate;
}

glm::mat4 GObject::GetModelMatrix()
{
    if (fMatrixAutoUpdate)
    {
        UpdateMatrix();
    }
    return fModelMatrix;
}

void GObject::SetModelMatrix(const glm::mat4& modelMatrix) 
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

void GObject::UpdateMatrix() 
{
    glm::mat4 parentMatrix;
    if (fParent)
    {
        parentMatrix = fParent->GetModelMatrix();
    }

    glm::mat4 localMatrix = glm::toMat4(fRotation);
    glm::scale(localMatrix, fScale);
    glm::translate(localMatrix, fPosition);
    localMatrix *= parentMatrix;
    fModelMatrix = localMatrix;
}

void GObject::Add(GObject* object) 
{
    fChildren.push_back(object);
    object->fParent = this;
}

void GObject::Attach(GObject* object) 
{
    glm::mat4 modelMatrix = GetModelMatrix();
    fChildren.push_back(object);
    object->fParent = this;
    SetModelMatrix(modelMatrix);
}