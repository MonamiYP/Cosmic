#pragma once

class IScene {
    public:
        virtual ~IScene() {}

        virtual bool Init() { return true; }
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Destroy() {}
    private:
};