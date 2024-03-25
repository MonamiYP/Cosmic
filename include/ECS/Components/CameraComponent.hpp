#pragma once

struct CameraComponent {
    float FOV = 70.0f;
    float pitch = glm::radians(15.0f);
    float distanceFromTarget = 5.0f;

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
};