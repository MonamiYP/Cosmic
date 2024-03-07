#pragma once

#include "Requirements.hpp"
#include "RequirementsECS.hpp"
#include "EngineConfig.hpp"
#include "Scenes/IScene.hpp"

class Engine {
    public:
        Engine(EngineConfig config = EngineConfig());
        bool Init();
        void Destroy();

        void Run();

        void SetActiveScene(IScene* scene);

        glm::vec2 GetWindowSize();
    
        static Engine* GetInstance;
        EngineConfig& config = m_config;
    private:
        GLFWwindow* m_window;
        void ImguiInit();
        void ImguiUpdate();
        void ImguiRender();
        void ImguiDestroy();

        EngineConfig m_config;
        IScene* m_scene = nullptr;
};