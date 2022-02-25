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
         * Max Pitch
         */
        float fMaxPitch;

        /**
         * @brief Min Pitch
         */
        float fMinPitch;


        /**
         * The y-rotation of the camera
         */
        float fYaw;

        /**
         * @brief Max Yaw
         * 
         */
        float fMaxYaw;

        /**
         * @brief Min Yaw
         * 
         */
        float fMinYaw;

        /**
         * The z-rotation of the camera
         */
        float fRoll;

        /**
         * @brief Max Roll
         */
        float fMaxRoll;

        /**
         * @brief Min Roll
         */
        float fMinRoll;

        /**
         * The zoom of the camera. Only used for ORTHOGRAPHIC Cameras
         * When using orthographic camera you should leave the the forward motion of the camera at 0
         */
        float fZoom;
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
         * Moves the camera up. Give negative value and the camera will move the the bottom.
         * @param amount The distance to move
         */
        void MoveUp(float amount);
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

        /**
         * @brief Get the Rotation in euler angles.
         * 
         * @return glm::vec3 
         */
        glm::vec3 GetRotationEuler() const;

        /**
         * @brief Set the zoom of the Camera. Only applied for ORTHOGRAPHIC Camera
         * @param zoom
         */
        void SetZoom(float zoom);
        float GetZoom() const;

        /**
         * @brief Set the max pitch of the camera.
         * 
         * @param maxPitch 
         */
        void SetMaxPitch(float maxPitch);

        /**
         * @brief Set the min pitch of the camera.
         * 
         * @param minPitch 
         */
        void SetMinPitch(float minPitch);

        /**
         * @brief Set the max yaw of the camera.
         * 
         * @param maxYaw 
         */
        void SetMaxYaw(float maxYaw);

        /**
         * @brief Set the min yaw of the camera.
         * 
         * @param minYaw 
         */
        void SetMinYaw(float minYaw);

        /**
         * @brief Set the max roll of the camera.
         * 
         * @param maxRoll 
         */
        void SetMaxRoll(float maxRoll);

        /**
         * @brief Set the min roll of the camera.
         * 
         * @param minRoll 
         */
        void SetMinRoll(float minRoll);

        glm::mat4 GetProjectionMatrix(unsigned int screenWidth, unsigned int screenHeight) const;
        glm::mat4 GetViewMatrix() const;

        ECameraMode GetMode() const;
    };

}