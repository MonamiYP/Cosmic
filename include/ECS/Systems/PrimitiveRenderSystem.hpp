#pragma once

#include "Requirements.hpp"
#include "RequirementsECS.hpp"

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include "Engine.hpp"

class PrimitiveRenderSystem : public System {
    public:
        void Init();
        void Draw(Entity* camera);
        void SetVAO();

    private:
        Shader m_shader;
        VertexArray m_VAO;
};