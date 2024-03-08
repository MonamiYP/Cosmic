#include "Systems/PrimitiveRenderSystem.hpp"
#include "Debug.hpp"

extern ECS ecs;

void PrimitiveRenderSystem::Init() {
    std::string vertex_source = m_shader.ParseShader("../res/shaders/vertex_shader.vs");
    std::string fragment_source = m_shader.ParseShader("../res/shaders/light_shader.fs");
    m_shader.CreateShaderProgram(vertex_source, fragment_source);
    m_shader.Bind();
    m_shader.SetVector3("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));
}

void PrimitiveRenderSystem::SetVAO() {
    for (auto const& entity: m_Entities) {
        std::vector<float> cubeVertices = ecs.GetComponent<VertexComponent>(entity).vertices;
        VertexBuffer VBO(&cubeVertices[0], cubeVertices.size() * sizeof(GLfloat));
        VertexBufferLayout layout;
        layout.AddAttribute(3);
        GLCall(m_VAO.AddBuffer(VBO, layout));
        m_VAO.Unbind();
    }
}

void PrimitiveRenderSystem::Draw(Entity* camera) {
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
        m_shader.SetMatrix4("u_model", model);

        m_VAO.Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    }

    m_VAO.Unbind();
}