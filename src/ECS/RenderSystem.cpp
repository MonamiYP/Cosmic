#include "Systems/RenderSystem.hpp"
#include <iostream>
#include "Renderer.hpp"

extern ECS ecs;

extern const float WINDOW_WIDTH;
extern const float WINDOW_HEIGHT;

void RenderSystem::Init() {
    m_Camera = ecs.CreateEntity();
    ecs.AddComponent(m_Camera, TransformComponent {.position = glm::vec3(0.0f, 0.0f, 0.0f)});
    ecs.AddComponent(m_Camera, OrientationComponent {
        .forwards = glm::vec3(0.0f, 0.0f, -1.0f),
        .right = glm::vec3(1.0f, 0.0f, 0.0f),
        .up = glm::vec3(0.0f, 1.0f, 0.0f)});
    ecs.AddComponent(m_Camera, CameraComponent{.FOV = 40.0f, .pitch = 15.0f});

    m_shader = std::make_unique<Shader>();

    std::string vertex_source = m_shader->ParseShader("../res/shaders/vertex_shader.vs");
    std::string fragment_source = m_shader->ParseShader("../res/shaders/light_shader.fs");
    m_shader->CreateShaderProgram(vertex_source, fragment_source);
    m_shader->Bind();
    m_shader->SetVector3("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));

    float vertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f

};

    VertexBuffer VBO(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.AddAttribute(3);
    GLCall(m_VAO.AddBuffer(VBO, layout));
    m_VAO.Unbind();
}

void RenderSystem::Update(float deltaTime) {
    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto& cameraTransform = ecs.GetComponent<TransformComponent>(m_Camera);
    auto& cameraOrientation = ecs.GetComponent<OrientationComponent>(m_Camera);
    auto& camera = ecs.GetComponent<CameraComponent>(m_Camera);

    glm::mat4 view = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraOrientation.forwards, cameraOrientation.up);
    glm::mat4 projection = glm::perspective(camera.FOV, WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);

    for (auto const& entity : m_Entities) {
        auto const& transform = ecs.GetComponent<TransformComponent>(entity);
        m_shader->Bind();
        m_shader->SetMatrix4("u_view", view);
        m_shader->SetMatrix4("u_projection", projection);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::scale(model, transform.scale); 
        m_shader->SetMatrix4("u_model", model);

        m_VAO.Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    }

    m_VAO.Unbind();
}