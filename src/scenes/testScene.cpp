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
    m_characterControlSystem->Update(deltaTime);
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
    ecs.RegisterComponent<InputComponent>();
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

    m_characterControlSystem = ecs.RegisterSystem<CharacterControlSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<TransformComponent>());
        signature.set(ecs.GetComponentType<InputComponent>());
        ecs.SetSystemSignature<CharacterControlSystem>(signature);
    }
    m_characterControlSystem->Init();
}

void TestScene::CreateEntities() {
    m_camera = ecs.CreateEntity();
    ecs.AddComponent(m_camera, TransformComponent {.position = glm::vec3(0.0f, 0.0f, 10.0f), .scale = glm::vec3(1.0f)});
    ecs.AddComponent(m_camera, OrientationComponent {});
    ecs.AddComponent(m_camera, CameraComponent{.FOV = 40.0f, .pitch = 15.0f});

    Model model;
    model.SetModelFromSource("../res/assets/spaceship/space_ship3.obj");
    Entity player = ecs.CreateEntity();
    ecs.AddComponent(player, TransformComponent { .position = glm::vec3(0.0f, -2.0f, 0.0f)});
    ecs.AddComponent(player, ModelComponent { .model = model });
    ecs.AddComponent(player, InputComponent { .yes = true });
    ecs.AddComponent(player, OrientationComponent {});

    std::vector<float> cubeVertices = GenerateVertices::GetCubeVertices();
    Entity light = ecs.CreateEntity();
    ecs.AddComponent(light, TransformComponent {});
    ecs.AddComponent(light, VertexComponent { .vertices =  cubeVertices });
    
    Entity light2 = ecs.CreateEntity();
    ecs.AddComponent(light2, TransformComponent { .position = glm::vec3(5.0f, 0.0f, -10.0f)});
    ecs.AddComponent(light2, VertexComponent { .vertices = cubeVertices });
}