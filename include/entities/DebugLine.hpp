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
        
        std::vector<float> GetVertices() { return m_vertices; }
        void SetLineVertices(const glm::vec3& start, const glm::vec3& end);

        void SetPosition(const glm::vec3& position) { m_position = position; }
        void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
        void SetLocalVectors(const glm::vec3& up, const glm::vec3& forwards, const glm::vec3& right);

        void Render(const VertexArray& va);
        glm::mat4 GetModelMatrix();
    private:
        std::vector<float> m_vertices;

        glm::vec3 m_position;
        glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_scale;

        glm::vec3 m_up = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_forwards = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_right = glm::vec3(0.0f, 1.0f, 0.0f);
};
