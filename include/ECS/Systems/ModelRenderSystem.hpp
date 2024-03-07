#pragma once

#include "RequirementsECS.hpp"

#include "VertexArray.hpp"
#include "Shader.hpp"

class ModelRenderSystem : public System {
    public:
        void Init();
        void Draw(float deltaTime);
    private:
        std::unique_ptr<Shader> m_shader;
        VertexArray m_VAO;
};