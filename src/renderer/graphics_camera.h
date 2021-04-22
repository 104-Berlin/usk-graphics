#pragma once

namespace Renderer {

    enum class ECameraMode
    {
        ORTHOGRAPHIC = 0,
        PERSPECTIVE = 1
    };

    /**
     * Basic Math for creating the Camera matricies.
     */
    class RCamera
    {
    private:
        /**
         * Projection or Orthographic Camera?
         */
        ECameraMode fCameraMode;

        /**
         * Eye position of the camera.
         * Change this via the Move functions
         */
        glm::vec3   fPosition;

        /**
         * The x-rotation of the camera
         */
        float fPitch;

        /**
         * The y-rotation of the camera
         */
        float fYaw;

        /**
         * The z-rotation of the camera
         */
        float fRoll;
    public:
        RCamera(ECameraMode cameraMode, const glm::vec3& position = glm::vec3());

        /**
         * Moves the camera forward. Give negative value and the camera will move backwards.
         * @param amount The distance to move.
         */
        void MoveForward(float amount);
        /**
         * Moves the camera to the right. Give negative value and the camera will move to the left.
         * @param amount The distance to move.
         */
        void MoveRight(float amount);
        /**
         * Turns the camera around the z-axis. Positive values will result in a right turn.
         * @param angle The angle to rotate. Use radian here.
         */
        void TurnRight(float angle);
        /**
         * Turns the camera around the x-axis. Positive values will result i a up turn.
         * @param angle The angle to rotate. Use radian here.
         */
        void TurnUp(float angle);

        /**
         * @return The vector pointing forward.
         */
        glm::vec3 GetForward() const;
        /**
         * @return The vector pointing to the right.
         */
        glm::vec3 GetRight() const;
        /**
         * @return The vector pointing upward.
         */
        glm::vec3 GetUp() const;

        /**
         * @param position New position of camera.
         */
        void SetPosition(const glm::vec3& position);

        /**
         * @return Current position of the camera
         */
        const glm::vec3& GetPosition() const;

        glm::mat4 GetProjectionMatrix(unsigned int screenWidth, unsigned int screenHeight);
        glm::mat4 GetViewMatrix();
    };

}