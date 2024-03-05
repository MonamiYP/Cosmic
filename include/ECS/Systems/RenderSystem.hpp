#pragma once

#include "ECS/ECS.hpp"
#include "ECS/System.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/OrientationComponent.hpp"
#include "Components/CameraComponent.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Player.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class RenderSystem : public System {
    public:
        void Init();
        void Update(float deltaTime);

    private:
        Entity m_Camera;
        std::unique_ptr<Shader> m_shader;

        VertexArray m_VAO;
};