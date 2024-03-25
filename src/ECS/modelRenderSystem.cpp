#include "Systems/ModelRenderSystem.hpp"

extern ECS ecs;

void ModelRenderSystem::Init() {
    std::string vertex_source = m_shader.ParseShader("../res/shaders/vertex_shader.vs");
    std::string fragment_source = m_shader.ParseShader("../res/shaders/fragment_shader.fs");
    m_shader.CreateShaderProgram(vertex_source, fragment_source);
    m_shader.Bind();
    m_shader.SetVector3("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));
    m_shader.SetVector3("lightPos", glm::vec3(1.0f, 0.0f, 0.0f));
    m_shader.SetFloat("constant",  1.0f);
    m_shader.SetFloat("linear",    0.014f);
    m_shader.SetFloat("quadratic", 0.0007f);
}

void ModelRenderSystem::Draw(Entity* camr) {
    auto& camera = ecs.GetComponent<CameraComponent>(*camr);

    glm::mat4 view = camera.view;
    glm::mat4 projection = camera.projection;

    m_shader.Bind();
    m_shader.SetMatrix4("u_view", view);
    m_shader.SetMatrix4("u_projection", projection);

    for (auto const& entity : m_Entities) {
        auto const& transform = ecs.GetComponent<TransformComponent>(entity);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
        model = glm::scale(model, transform.scale);
        if (ecs.HasComponent<OrientationComponent>(entity)) {
            auto const& orientation = ecs.GetComponent<OrientationComponent>(entity);
            model = model * orientation.rotMatrix;
        }
        m_shader.SetMatrix4("u_model", model);

        auto& entity_model = ecs.GetComponent<ModelComponent>(entity);
        entity_model.model.Draw(m_shader); 
    }
}