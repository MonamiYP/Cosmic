#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Player.hpp"

class Camera {
    private:
        glm::vec3 m_position;
        glm::vec3 m_forwards;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        float m_yaw;
        float m_pitch;

        float m_movementSpeed;
        float m_mouseSensitivity;
        float m_fov;
    public:
        Camera(const Player& player);
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                float yaw = -90.0f, float pitch = -10.0f);
        ~Camera() {}

        glm::mat4 GetCameraView();
        void UpdateVectors();

        float GetFOV();
        glm::vec3 GetPosition();
        glm::vec3 GetForwards();
};