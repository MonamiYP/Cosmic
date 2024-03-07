#pragma once

#include "RequirementsECS.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.hpp"
#include "Shader.hpp"
#include "Player.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include "Engine.hpp"

class RenderSystem : public System {
    public:
        void Init();
        void Draw(float deltaTime);

    private:
        Entity m_Camera;
        std::unique_ptr<Shader> m_shader;

        VertexArray m_VAO;
};