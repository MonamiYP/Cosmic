#include "Engine.hpp"

ECS ecs;

int main() {
    Engine gameEngine;

    if (gameEngine.Init()) {
        gameEngine.Run();
    }

    gameEngine.Destroy();

    return 0;
}