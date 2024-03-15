#include "Scenes/TestScene.hpp"

extern ECS ecs;

TestScene::TestScene() {
    RegisterComponents();
    RegisterSystems();
    CreateEntities();
    m_primitiveRenderSystem->SetVAO();
    m_planetRenderSystem->SetVAO();

    std::vector<std::string> faces { 
        "../res/assets/space_skybox/right.png", 
        "../res/assets/space_skybox/left.png", 
        "../res/assets/space_skybox/top.png", 
        "../res/assets/space_skybox/bottom.png", 
        "../res/assets/space_skybox/front.png", 
        "../res/assets/space_skybox/back.png" };
    m_skyBoxTexture = m_skybox.loadSkyBox(faces);

    std::string vertex_source = m_skyBoxShader.ParseShader("../res/shaders/skybox.vs");
    std::string fragment_source = m_skyBoxShader.ParseShader("../res/shaders/skybox.fs");
    m_skyBoxShader.CreateShaderProgram(vertex_source, fragment_source);
    m_skyBoxShader.Bind();
    m_skyBoxShader.SetInt("skybox", 0);

    std::vector<float> cubeVertices = GenerateVertices::GetCubeVertices();
    VertexBuffer VBO(&cubeVertices[0], cubeVertices.size() * sizeof(GLfloat));
    VertexBufferLayout layout;
    layout.AddAttribute(3);
    m_skyBoxVAO.AddBuffer(VBO, layout);
    m_skyBoxVAO.Unbind();
}

TestScene::~TestScene() {}

void TestScene::ProcessKeyboardInput(MovementDir dir, float deltaTime) {
    m_movementSystem->ProcessKeyboardInput(dir, deltaTime);
}

void TestScene::ProcessMouseInput(float xOffset, float yOffset) {
    m_movementSystem->ProcessMouseInput(xOffset, yOffset);
}

void TestScene::Update(float deltaTime) {
    m_movementSystem->Update(deltaTime, &m_camera);
}

void TestScene::Render() {
    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDepthFunc(GL_LEQUAL);
    m_skyBoxShader.Bind();
    auto& camera = ecs.GetComponent<CameraComponent>(m_camera);
    m_skyBoxShader.SetMatrix4("u_view", glm::mat4(glm::mat3(camera.view)));
    m_skyBoxShader.SetMatrix4("u_projection", camera.projection);

    m_skyBoxVAO.Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyBoxTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
    
    m_primitiveRenderSystem->Draw(&m_camera);
    m_modelRenderSystem->Draw(&m_camera);
    m_planetRenderSystem->Draw(&m_camera);
}

void TestScene::RegisterComponents() {
    ecs.RegisterComponent<TransformComponent>();
    ecs.RegisterComponent<OrientationComponent>();
    ecs.RegisterComponent<CameraComponent>();
    ecs.RegisterComponent<ModelComponent>();
    ecs.RegisterComponent<VertexComponent>();
    ecs.RegisterComponent<InputComponent>();
    ecs.RegisterComponent<LightComponent>();
    ecs.RegisterComponent<PlanetComponent>();
}

void TestScene::RegisterSystems() {
    m_primitiveRenderSystem = ecs.RegisterSystem<PrimitiveRenderSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<LightComponent>());
        signature.set(ecs.GetComponentType<VertexComponent>());
        ecs.SetSystemSignature<PrimitiveRenderSystem>(signature);
    }
    m_primitiveRenderSystem->Init();

    m_planetRenderSystem = ecs.RegisterSystem<PlanetRenderSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<PlanetComponent>());
        signature.set(ecs.GetComponentType<VertexComponent>());
        ecs.SetSystemSignature<PlanetRenderSystem>(signature);
    }
    m_planetRenderSystem->Init();

    m_modelRenderSystem = ecs.RegisterSystem<ModelRenderSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<TransformComponent>());
        signature.set(ecs.GetComponentType<ModelComponent>());
        ecs.SetSystemSignature<ModelRenderSystem>(signature);
    }
    m_modelRenderSystem->Init();

    m_movementSystem = ecs.RegisterSystem<MovementSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<TransformComponent>());
        signature.set(ecs.GetComponentType<InputComponent>());
        ecs.SetSystemSignature<MovementSystem>(signature);
    }
    m_movementSystem->Init();
}

void TestScene::CreateEntities() {
    m_camera = ecs.CreateEntity();
    ecs.AddComponent(m_camera, TransformComponent {});
    ecs.AddComponent(m_camera, OrientationComponent {});
    ecs.AddComponent(m_camera, CameraComponent{});

    Model model;
    model.SetModelFromSource("../res/assets/spaceship/space_ship3.obj");
    Entity player = ecs.CreateEntity();
    ecs.AddComponent(player, TransformComponent { .position = glm::vec3(0.0f, -2.0f, 0.0f), .scale = glm::vec3(0.1f)});
    ecs.AddComponent(player, ModelComponent { .model = model });
    ecs.AddComponent(player, InputComponent { .yes = true });
    ecs.AddComponent(player, OrientationComponent {});

    std::vector<float> cubeVertices = GenerateVertices::GetCubeVertices();
    Entity light = ecs.CreateEntity();
    ecs.AddComponent(light, TransformComponent { .scale = glm::vec3(0.1f) });
    ecs.AddComponent(light, VertexComponent { .vertices =  cubeVertices, .indicesCount = 36 });
    ecs.AddComponent(light, LightComponent { .lightColor = glm::vec3(1.0f, 1.0f, 1.0f) });
    
    Entity light2 = ecs.CreateEntity();
    ecs.AddComponent(light2, TransformComponent { .position = glm::vec3(5.0f, 0.0f, -10.0f), .scale = glm::vec3(0.1f)});
    ecs.AddComponent(light2, VertexComponent { .vertices = cubeVertices, .indicesCount = 36 });
    ecs.AddComponent(light2, LightComponent { .lightColor = glm::vec3(1.0f, 1.0f, 1.0f) });

    Entity planet = ecs.CreateEntity();
    float resolution = 10;
    float radius = 1000.0f;
    ecs.AddComponent(planet, TransformComponent { .position = glm::vec3(radius, radius, radius) });
    ecs.AddComponent(planet, VertexComponent { .vertices = GenerateVertices::GetSphereVertices(radius, resolution), .indicesCount = 4*resolution*resolution*6 });
    ecs.AddComponent(planet, PlanetComponent { .radius = radius });
}