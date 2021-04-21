#include "graphics_renderer.h"

using namespace Renderer;

RCamera::RCamera(ECameraMode cameraMode, const glm::vec3& position)
    : fCameraMode(cameraMode), fPosition(position), fForward(0.0f, 0.0f, -1.0f), fUpward(0.0f, 1.0f, 0.0f)
{
}

glm::mat4 RCamera::GetProjectionMatrix(unsigned int screenWidth, unsigned int screenHeight) 
{
    switch (fCameraMode)
    {
    case ECameraMode::ORTHOGRAPHIC: return glm::ortho(-(float)screenWidth/2, (float)screenWidth/2, -(float)screenHeight/2, (float)screenHeight/2);
    case ECameraMode::PERSPECTIVE: return glm::perspective(60.0f, (float)screenWidth/(float)screenHeight, 0.00001f, 100000.0f);
    }
    return glm::mat4();
}

glm::mat4 RCamera::GetViewMatrix() 
{
    return glm::lookAt(fPosition, fPosition + fForward, fUpward);
}
