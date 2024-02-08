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

std::vector<float> DebugLine::GetVertices() {
    return m_vertices;
}

void DebugLine::SetPosition(const glm::vec3& position) {
    m_position = position;
}

glm::mat4 DebugLine::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);

    return model;
}

void DebugLine::Render(const VertexArray& va) {
    va.Bind();
    GLCall(glDrawArrays(GL_LINES, 0, 2));
}