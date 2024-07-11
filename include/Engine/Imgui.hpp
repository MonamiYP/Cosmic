#pragma once

#include "Requirements.hpp"

class Imgui {
    public:
        Imgui() {};
        void Init(GLFWwindow* window);
        void Update();
        void Render();
        void Destroy();
        float* GetColor() { return m_color; }
    
    private:
        float m_color[3];
};