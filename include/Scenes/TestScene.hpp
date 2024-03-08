#pragma once

#include "Requirements.hpp"
#include "Scenes/IScene.hpp"
#include "RequirementsECS.hpp"
#include "Systems/ModelRenderSystem.hpp"
#include "Systems/PrimitiveRenderSystem.hpp"
#include "Systems/CharacterControlSystem.hpp"
#include "GenerateVertices.hpp"

class TestScene : public IScene {
    public:
        TestScene();
        ~TestScene();
        void Update(float deltaTime) override;
        void Render() override;
    private:
        void RegisterComponents();
        void RegisterSystems();
        void CreateEntities();

        Entity m_camera;
        std::shared_ptr<PrimitiveRenderSystem> m_primitiveRenderSystem;
        std::shared_ptr<ModelRenderSystem> m_modelRenderSystem;
        std::shared_ptr<CharacterControlSystem> m_characterControlSystem;
};