#include "DebugLine.hpp"
#include "Renderer.hpp"

DebugLine::DebugLine(const glm::vec3 start, const glm::vec3 end) {
    m_vertices.clear();
    m_vertices.push_back(start.x);
    m_vertices.push_back(start.y);
    m_vertices.push_back(start.z);
    m_vertices.push_back(end.x);
    m_vertices.push_back(end.y);
    m_vertices.push_back(end.z);
}

void DebugLine::SetLineVertices(const glm::vec3& start, const glm::vec3& end) {
    m_vertices.clear();
    m_vertices.push_back(start.x);
    m_vertices.push_back(start.y);
    m_vertices.push_back(start.z);
    m_vertices.push_back(end.x);
    m_vertices.push_back(end.y);
    m_vertices.push_back(end.z);
}

void DebugLine::SetLocalVectors(const glm::vec3& up, const glm::vec3& forwards, const glm::vec3& right) {
    m_up = up;
    m_forwards = forwards;
    m_right = right;
}

glm::mat4 DebugLine::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.z), m_forwards);

    return model;
}

void DebugLine::Render(const VertexArray& va) {
    va.Bind();
    GLCall(glDrawArrays(GL_LINES, 0, 2));
}