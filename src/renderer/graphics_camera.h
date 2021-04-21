#pragma once

namespace Renderer {

    enum class ECameraMode
    {
        ORTHOGRAPHIC = 0,
        PERSPECTIVE = 1
    };

    class RCamera
    {
    private:
        ECameraMode fCameraMode;
        glm::vec3   fPosition;
        glm::vec3   fForward;
        glm::vec3   fUpward;
    public:
        RCamera(ECameraMode cameraMode, const glm::vec3& position = glm::vec3());

        glm::mat4 GetProjectionMatrix(unsigned int screenWidth, unsigned int screenHeight);
        glm::mat4 GetViewMatrix();
    };

}