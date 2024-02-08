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

    SetupShader();
}

void DebugLine::SetupShader() {
    std::string vertex_source = shader.ParseShader("../res/shaders/debug_line.vs");
    std::string fragment_source = shader.ParseShader("../res/shaders/debug_line.fs");
    shader.CreateShaderProgram(vertex_source, fragment_source);
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

void DebugLine::Render(glm::mat4& view, glm::mat4& projection, const VertexArray& va) {
    va.Bind();
    shader.Bind();
    shader.SetMatrix4("u_view", view);
    shader.SetMatrix4("u_projection", projection);
    GLCall(glDrawArrays(GL_LINES, 0, 2));
}