#pragma once

#include <glm/glm.hpp>

struct OrientationComponent {
    glm::vec3 forwards = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

    glm::mat4 rotMatrix = glm::mat4(1.0f);
};