#pragma once

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class DebugLine {
    public:
        DebugLine(const glm::vec3 start, const glm::vec3 end);
        ~DebugLine() {}
        
        std::vector<float> GetVertices();
        void SetLineVertices(const glm::vec3& start, const glm::vec3& end);
        void SetPosition(const glm::vec3& position);
        void Render(const VertexArray& va);
        glm::mat4 GetModelMatrix();
    private:
        std::vector<float> m_vertices;
        glm::vec3 m_position;
};
