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

void ModelRenderSystem::Draw(Entity* camera) {
    auto& cameraTransform = ecs.GetComponent<TransformComponent>(*camera);
    auto& cameraOrientation = ecs.GetComponent<OrientationComponent>(*camera);
    auto& camera_C = ecs.GetComponent<CameraComponent>(*camera);

    glm::mat4 view = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraOrientation.forwards, cameraOrientation.up);
    glm::mat4 projection = glm::perspective(camera_C.FOV, Engine::GetInstance->GetWindowSize().x/Engine::GetInstance->GetWindowSize().y, 0.1f, 100.0f);

    for (auto const& entity : m_Entities) {
        auto const& transform = ecs.GetComponent<TransformComponent>(entity);
        m_shader.Bind();
        m_shader.SetMatrix4("u_view", view);
        m_shader.SetMatrix4("u_projection", projection);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
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