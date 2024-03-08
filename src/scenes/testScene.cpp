#include "Scenes/TestScene.hpp"

extern ECS ecs;

TestScene::TestScene() {
    RegisterComponents();
    RegisterSystems();
    CreateEntities();
    m_primitiveRenderSystem->SetVAO();
}

TestScene::~TestScene() {}

void TestScene::Update(float deltaTime) {
    
}

void TestScene::Render() {
    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_primitiveRenderSystem->Draw(&m_camera);
    m_modelRenderSystem->Draw(&m_camera);
}

void TestScene::RegisterComponents() {
    ecs.RegisterComponent<TransformComponent>();
    ecs.RegisterComponent<OrientationComponent>();
    ecs.RegisterComponent<CameraComponent>();
    ecs.RegisterComponent<ModelComponent>();
    ecs.RegisterComponent<VertexComponent>();
}

void TestScene::RegisterSystems() {
    m_primitiveRenderSystem = ecs.RegisterSystem<PrimitiveRenderSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<TransformComponent>());
        signature.set(ecs.GetComponentType<VertexComponent>());
        ecs.SetSystemSignature<PrimitiveRenderSystem>(signature);
    }
    m_primitiveRenderSystem->Init();

    m_modelRenderSystem = ecs.RegisterSystem<ModelRenderSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<TransformComponent>());
        signature.set(ecs.GetComponentType<ModelComponent>());
        ecs.SetSystemSignature<ModelRenderSystem>(signature);
    }
    m_modelRenderSystem->Init();
}

void TestScene::CreateEntities() {
    m_camera = ecs.CreateEntity();
    ecs.AddComponent(m_camera, TransformComponent {.position = glm::vec3(0.0f, 0.0f, 0.0f), .scale = glm::vec3(1.0f)});
    ecs.AddComponent(m_camera, OrientationComponent {
        .forwards = glm::vec3(0.0f, 0.0f, -1.0f),
        .right = glm::vec3(1.0f, 0.0f, 0.0f),
        .up = glm::vec3(0.0f, 1.0f, 0.0f)});
    ecs.AddComponent(m_camera, CameraComponent{.FOV = 40.0f, .pitch = 15.0f});

    Model model;
    model.SetModelFromSource("../res/assets/spaceship/space_ship3.obj");
    Entity player = ecs.CreateEntity();
    ecs.AddComponent(player, TransformComponent {
        .position = glm::vec3(0.0f, -2.0f, -10.0f),
        .scale = glm::vec3(1.0f)});
    ecs.AddComponent(player, ModelComponent { .model = model });

    std::vector<float> cubeVertices = GenerateVertices::GetCubeVertices();
    Entity light = ecs.CreateEntity();
    ecs.AddComponent(light, TransformComponent {
        .position = glm::vec3(0.0f, 0.0f, -10.0f),
        .scale = glm::vec3(1.0f)});
    ecs.AddComponent(light, VertexComponent {
        .vertices =  cubeVertices });
    
    Entity light2 = ecs.CreateEntity();
    ecs.AddComponent(light2, TransformComponent {
        .position = glm::vec3(5.0f, 0.0f, -10.0f),
        .scale = glm::vec3(1.0f)});
    ecs.AddComponent(light2, VertexComponent {
        .vertices = cubeVertices });
}