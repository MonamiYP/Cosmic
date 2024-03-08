#pragma once

class IScene {
    public:
        virtual ~IScene() {}
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;
    private:
};