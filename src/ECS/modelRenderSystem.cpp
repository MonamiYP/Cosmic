#include "Systems/ModelRenderSystem.hpp"

void ModelRenderSystem::Init() {
    m_VAO.Bind();

    m_shader = std::make_unique<Shader>();
}

void ModelRenderSystem::Draw(float deltaTime) {

}