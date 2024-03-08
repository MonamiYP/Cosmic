#include "Engine.hpp"

ECS ecs;

int main() {
    ecs.Init();
    Engine gameEngine;

    if (gameEngine.Init()) {
        gameEngine.Run();
    }

    gameEngine.Destroy();

    return 0;
}