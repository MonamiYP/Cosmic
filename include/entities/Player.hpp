#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.hpp"
#include "Shader.hpp"

enum MovementDir {
    UP, DOWN, LEFT, RIGHT, FORWARDS, BACKWARDS
};

class Player {
    public:
        Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = -90.0f, float pitch = 0.0f);
        ~Player() {}

        void SetModelFromSource(std::string const& path);
        void Render(Shader& shader);

        void ProcessKeyboardInput(MovementDir dir, float deltaTime);
        void ProcessMouseInput(float xOffset, float yOffset);
        void UpdateVectors();
        glm::vec3 GetPosition();
        glm::vec3 GetForwardDir();
        glm::mat4 GetModelMatrix();
    private:
        float m_movementSpeed;
        float m_rollSpeed;
        float m_mouseSensitivity;

        float m_yaw;
        float m_pitch;
        float m_roll;

        glm::vec3 m_position;
        glm::vec3 m_forwards;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        Model m_playerModel;
};