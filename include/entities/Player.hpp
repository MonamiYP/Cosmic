#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.hpp"
#include "Shader.hpp"

class Player {
    public:
        Player();
        ~Player() {}

        void SetModelFromSource(std::string const& path);
        void Render(Shader& shader);

        glm::vec3 ProcessKeyboardInput();
        glm::vec3 GetPosition();
        glm::vec3 GetForwardDir();
    private:
        glm::vec3 m_position;
        Model m_playerModel;
};