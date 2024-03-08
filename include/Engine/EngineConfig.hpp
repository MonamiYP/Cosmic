#pragma once

struct EngineConfig {
    float WINDOW_WIDTH = 1200.0f;
    float WINDOW_HEIGHT = 800.0f;

    float lastX =  WINDOW_WIDTH / 2.0;
    float lastY =  WINDOW_HEIGHT / 2.0;

    bool guiActive = false;

    float deltaTime;
    float lastTime;

    int outerTesselationLevel = 15;
    int innerTesselationLevel = 15;
};