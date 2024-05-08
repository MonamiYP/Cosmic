#include "Systems/LightSystem.hpp"

extern ECS ecs;

void LightSystem::Init() {

}

void LightSystem::SetupShaderLights(Shader* shader) {
    shader->Bind();
    int index = 0;
    for (auto const& entity : m_Entities) {
        if (ecs.HasComponent<LightComponent>(entity)) {
            auto const& light = ecs.GetComponent<LightComponent>(entity);
            auto const& transform = ecs.GetComponent<TransformComponent>(entity);
            
            shader->SetFloat("pointLights["+std::to_string(index)+"].constant",  light.constant);
            shader->SetFloat("pointLights["+std::to_string(index)+"].linear",    light.linear);
            shader->SetFloat("pointLights["+std::to_string(index)+"].quadratic", light.quadratic);

            shader->SetVector3("pointLights["+std::to_string(index)+"].position", transform.position);
            shader->SetVector3("pointLights["+std::to_string(index)+"].ambient", light.ambient);
            shader->SetVector3("pointLights["+std::to_string(index)+"].diffuse", light.diffuse);
            shader->SetVector3("pointLights["+std::to_string(index)+"].specular", light.specular);
            index++;
        }
    }

    shader->SetInt("no_pointLights", index);
}