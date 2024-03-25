#pragma once

#include "Requirements.hpp"
#include "RequirementsECS.hpp"

#include "VertexArray.hpp"
#include "Shader.hpp"

#include "Engine.hpp"

class ModelRenderSystem : public System {
    public:
        void Init();
        void Draw(Entity* camera);
    private:
        Shader m_shader;
        VertexArray m_VAO;
};