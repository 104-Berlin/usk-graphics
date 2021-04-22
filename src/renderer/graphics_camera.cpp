#include "graphics_renderer.h"

using namespace Renderer;

RCamera::RCamera(ECameraMode cameraMode, const glm::vec3& position)
    : fCameraMode(cameraMode), fPosition(position), fPitch(0.0f), fYaw(0.0f), fRoll(0.0f)
{
}

void RCamera::MoveForward(float amount) 
{
    fPosition += GetForward() * amount;
}

void RCamera::MoveRight(float amount) 
{
    fPosition += GetRight() * amount;
}

void RCamera::MoveUp(float amount) 
{
    fPosition += GetUp() * amount;
}

void RCamera::TurnRight(float angle) 
{
    fYaw += angle;
}

void RCamera::TurnUp(float angle) 
{
    fPitch += angle;
}

glm::vec3 RCamera::GetForward() const
{
    return glm::normalize(glm::vec3{sinf(fYaw) * cosf(fPitch), sinf(fPitch), cosf(fYaw) * cosf(fPitch)});
}

glm::vec3 RCamera::GetRight() const
{
    return glm::normalize(glm::cross(GetForward(), {0.0f, 1.0f, 0.0f}));
}

glm::vec3 RCamera::GetUp() const
{
    return glm::normalize(glm::cross(GetRight(), GetForward()));
}

void RCamera::SetPosition(const glm::vec3& position) 
{
    fPosition = position;
}

const glm::vec3& RCamera::GetPosition() const
{
    return fPosition;
}

glm::mat4 RCamera::GetProjectionMatrix(unsigned int screenWidth, unsigned int screenHeight) 
{
    if (screenWidth == 0 || screenHeight == 0) { return glm::mat4(); }
    switch (fCameraMode)
    {
    case ECameraMode::ORTHOGRAPHIC: return glm::ortho(-(float)screenWidth/2, (float)screenWidth/2, -(float)screenHeight/2, (float)screenHeight/2);
    case ECameraMode::PERSPECTIVE: return glm::perspective(90.0f, (float)screenWidth/(float)screenHeight, 0.00001f, 100000.0f);
    }
    return glm::mat4();
}

glm::mat4 RCamera::GetViewMatrix() 
{
    return glm::lookAt(fPosition, fPosition + GetForward(), GetUp());
}
