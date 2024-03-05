#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Player.hpp"

class Camera {
    private:
        Player* m_player;
        glm::vec3 m_position;
        glm::vec3 m_forwards;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        float m_fov;
        float m_distanceFromPlayer;
    public:
        Camera(Player* player);
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                float yaw = -90.0f, float pitch = -10.0f);
        ~Camera() {}

        glm::mat4 GetCameraView();
        void UpdateVectors();

        float GetFOV();
        glm::vec3 GetPosition();
        glm::vec3 GetForwards();
        glm::vec3 GetUpDir() { return m_up; }
};