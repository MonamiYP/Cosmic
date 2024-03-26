#pragma once

#include "Requirements.hpp"
#include "Scenes/IScene.hpp"
#include "RequirementsECS.hpp"
#include "GenerateVertices.hpp"
#include "Directions.hpp"
#include "SkyBox.hpp"

class TestScene : public IScene {
    public:
        TestScene();
        ~TestScene();
        void Update(float deltaTime) override;
        void Render() override;
        void ProcessKeyboardInput(MovementDir dir, float deltaTime) override;
        void ProcessMouseInput(float xOffset, float yOffset) override;
    private:
        void RegisterComponents();
        void RegisterSystems();
        void CreateEntities();

        Entity m_camera;
        SkyBox m_skybox;
        Shader m_skyBoxShader;
        unsigned int m_skyBoxTexture;
        VertexArray m_skyBoxVAO;

        std::shared_ptr<PrimitiveRenderSystem> m_primitiveRenderSystem;
        std::shared_ptr<PlanetRenderSystem> m_planetRenderSystem;
        std::shared_ptr<ModelRenderSystem> m_modelRenderSystem;
        std::shared_ptr<MovementSystem> m_movementSystem;
        std::shared_ptr<LightSystem> m_lightSystem;
};