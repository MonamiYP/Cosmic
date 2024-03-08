#pragma once

#include "Requirements.hpp"
#include "RequirementsECS.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

enum MovementDir {
    UP, DOWN, LEFT, RIGHT, FORWARDS, BACKWARDS
};

class CharacterControlSystem : public System {
    public:
        void Init();
        void Update(float deltaTime);

    private:
        glm::mat4 GetQuaternionMatrix(const Entity* entity);
        void SetRotationMatrix(const Entity* entity);

        void ProcessKeyboardInput(const Entity* entity, MovementDir dir, float deltaTime);
        void ProcessMouseInput(const Entity* entity, float xOffset, float yOffset);

        float m_movementSpeed = 100.0f;
        float m_rollSpeed = 50.0f;
        float m_mouseSensitivity = 0.02f;
        glm::mat4 m_prev_rot = glm::mat4(1.0f);
};