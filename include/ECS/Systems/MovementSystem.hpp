#pragma once

#include "Requirements.hpp"
#include "RequirementsECS.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Directions.hpp"
#include "Engine.hpp"

class MovementSystem : public System {
    public:
        void Init();
        void Update(float deltaTime, Entity* camera);

        void ProcessKeyboardInput(MovementDir dir, float deltaTime);
        void ProcessMouseInput(float xOffset, float yOffset);
        void SetCamera(TransformComponent const& transform, OrientationComponent const& orientation);
    private:
        glm::mat4 GetQuaternionMatrix(const Entity* entity);
        void SetRotationMatrix(const Entity* entity);

        float m_movementSpeed = 100.0f;
        float m_rollSpeed = 100.0f;
        float m_mouseSensitivity = 0.02f;
        glm::mat4 m_prev_rot = glm::mat4(1.0f);
};