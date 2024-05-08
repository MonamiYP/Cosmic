#include "Systems/PlanetRenderSystem.hpp"
#include "Debug.hpp"

extern ECS ecs;

void PlanetRenderSystem::Init() {
    std::string vertex_source = m_shader.ParseShader("../res/shaders/planet.vs");
    std::string tesc_source = m_shader.ParseShader("../res/shaders/planet.tesc");
    std::string tese_source = m_shader.ParseShader("../res/shaders/planet.tese");
    std::string fragment_source = m_shader.ParseShader("../res/shaders/planet.fs");
    m_shader.CreateShaderProgram(vertex_source, tesc_source, tese_source, fragment_source);
    m_shader.Bind();

    for (auto const& entity: m_Entities) {
        std::vector<float> planetVertices = ecs.GetComponent<VertexComponent>(entity).vertices;
        VertexBuffer VBO(&planetVertices[0], planetVertices.size() * sizeof(GLfloat));
        VertexBufferLayout layout;
        layout.AddAttribute(3);
        GLCall(m_VAO.AddBuffer(VBO, layout));
        m_VAO.Unbind();
    }
}

void PlanetRenderSystem::Draw(Entity* camr) {
    auto& camera = ecs.GetComponent<CameraComponent>(*camr);
    auto& cameraTransform = ecs.GetComponent<TransformComponent>(*camr);

    glm::mat4 view = camera.view;
    glm::mat4 projection = camera.projection;

    m_shader.Bind();
    m_shader.SetMatrix4("u_view", view);
    m_shader.SetMatrix4("u_projection", projection);

    glDepthMask(GL_TRUE);
    m_VAO.Bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (auto const& entity : m_Entities) {
        auto const& transform = ecs.GetComponent<TransformComponent>(entity);
        auto const& vertices = ecs.GetComponent<VertexComponent>(entity);
        auto const& planet = ecs.GetComponent<PlanetComponent>(entity);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::scale(model, transform.scale); 
        m_shader.SetMatrix4("u_model", model);
        m_shader.SetVector3("u_cameraPos", cameraTransform.position);

        m_shader.SetFloat("u_radius", planet.radius);

        GLCall(glDrawArrays(GL_PATCHES, 0, vertices.indicesCount));
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_VAO.Unbind();
}