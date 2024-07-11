#pragma once

#include "Directions.hpp"

class IScene {
    public:
        virtual ~IScene() {}
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;
        virtual void ProcessKeyboardInput(MovementDir dir, float deltaTime) = 0;
        virtual void ProcessMouseInput(float xOffset, float yOffset) = 0;
        virtual void ProcessMouseClick(float xpos, float ypos) = 0;
    private:
};