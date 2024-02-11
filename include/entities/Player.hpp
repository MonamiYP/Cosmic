#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Model.hpp"
#include "Shader.hpp"

enum MovementDir {
    UP, DOWN, LEFT, RIGHT, FORWARDS, BACKWARDS
};

class Player {
    public:
        Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            float yaw = -90.0f, float pitch = 0.0f);
        ~Player() {}

        void SetModelFromSource(std::string const& path);
        void Render(Shader& shader);

        void ProcessKeyboardInput(MovementDir dir, float deltaTime);
        void ProcessMouseInput(float xOffset, float yOffset);

        glm::mat4 GetQuaternionMatrix();

        glm::vec3 GetPosition() { return m_position; }
        glm::vec3 GetRotation() { return m_rotation; }
        glm::vec3 GetForwardDir() { return m_forwards; }
        glm::vec3 GetUpDir() { return m_up; }
        glm::vec3 GetRightDir() { return m_right; }
        glm::mat4 GetModelMatrix();
    private:
        glm::mat4 m_prev_rot = glm::mat4(1.0f);

        float m_movementSpeed = 8.0f;
        float m_rollSpeed = 80.0f;
        float m_mouseSensitivity = 0.05f;

        glm::vec3 m_position;
        glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_scale;

        glm::vec3 m_forwards;
        glm::vec3 m_up;
        glm::vec3 m_right;

        Model m_playerModel;
};