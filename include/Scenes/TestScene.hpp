#pragma once

#include "IScene.hpp"
#include "Camera.hpp"

class TestScene : public IScene {
    public:
        bool Init() override;
        void Update() override;
        void Render() override;
        void Destroy() override;

    private:
        Camera* m_camera = nullptr;
};