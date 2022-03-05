#include "graphics_renderer.h"

using namespace Renderer;

RCamera::RCamera(ECameraMode cameraMode, const glm::vec3& position)
    : fCameraMode(cameraMode), fPosition(position), fPitch(0.0f), fMaxPitch(100000.0f), fMinPitch(-100000.0f), fYaw(0.0f), fMaxYaw(100000.0f), fMinYaw(-100000.0f), fRoll(0.0f), fMaxRoll(100000.0f), fMinRoll(-100000.0f), fZoom(1.0f)
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
    fYaw = std::max(fYaw, fMinYaw);
    fYaw = std::min(fYaw, fMaxYaw);
    fYaw = std::fmod(fYaw, 2 * R_PI);
}

void RCamera::TurnUp(float angle) 
{
    fPitch += angle;
    fPitch = std::max(fPitch, fMinPitch);
    fPitch = std::min(fPitch, fMaxPitch);
    fPitch = std::fmodf(fPitch, 2.0f * R_PI);
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

glm::vec3 RCamera::GetRotationEuler() const
{
    return {fPitch, fYaw, fRoll};
}

void RCamera::SetZoom(float zoom) 
{
    fZoom = zoom;
}

float RCamera::GetZoom() const
{
    return fZoom;
}

void RCamera::SetMaxPitch(float maxPitch) 
{
    fMaxPitch = maxPitch;
}

void RCamera::SetMinPitch(float minPitch) 
{
    fMinPitch = minPitch;
}

void RCamera::SetMaxYaw(float maxYaw) 
{
    fMaxYaw = maxYaw;
}

void RCamera::SetMinYaw(float minYaw) 
{
    fMinYaw = minYaw;
}

void RCamera::SetMaxRoll(float maxRoll) 
{
    fMaxRoll = maxRoll;
}

void RCamera::SetMinRoll(float minRoll) 
{
    fMinRoll = minRoll;
}


glm::mat4 RCamera::GetProjectionMatrix(unsigned int screenWidth, unsigned int screenHeight) const
{
    if (screenWidth == 0 || screenHeight == 0) { return glm::mat4(); }
    switch (fCameraMode)
    {
    case ECameraMode::ORTHOGRAPHIC: return glm::ortho(0.0f, -(((float)screenWidth) * fZoom), (((float)screenHeight) * fZoom), 0.0f);
    case ECameraMode::PERSPECTIVE: return glm::perspectiveZO(R_PI / 4.0f, (((float)screenWidth) / (float)screenHeight), 0.1f, 1000.0f);
    }
    return glm::mat4();
}

glm::mat4 RCamera::GetViewMatrix() const
{
    return glm::lookAt(fPosition, fPosition + GetForward(), GetUp());
}

ECameraMode RCamera::GetMode() const
{
    return fCameraMode;
}
