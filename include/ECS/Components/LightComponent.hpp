#pragma once 

struct LightComponent {
    glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 specular = glm::vec3(0.0f, 0.0f, 0.0f);

    float constant = 1.0f;
    float linear = 0.014f;
    float quadratic = 0.0007f;
};