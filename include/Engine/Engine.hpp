#pragma once

#include "Requirements.hpp"
#include "RequirementsECS.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "EngineConfig.hpp"
#include "Scenes/IScene.hpp"
#include "Imgui.hpp"

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
        IScene* m_scene;
        
    private:
        GLFWwindow* m_window;
        EngineConfig m_config;
        Imgui m_imgui;
};