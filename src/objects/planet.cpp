#include "Planet.hpp"

Planet::Planet(int resolution, float diameter) {
    m_resolution = resolution;
    m_radius = diameter/2;
}

void Planet::CreateMesh() {
    float segment_width = m_radius*2/m_resolution;
    for (unsigned int j = 0; j < m_resolution; j++) {
        // Face 1
        for (unsigned int i = 0; i < m_resolution; i++) {
            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);
            m_vertices.push_back(-m_radius);

            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);
            m_vertices.push_back(-m_radius);
            
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);
            m_vertices.push_back(-m_radius);

            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);
            m_vertices.push_back(-m_radius);
        }
    }
    // Face 2
    for (unsigned int j = 0; j < m_resolution; j++) {
        for (unsigned int i = 0; i < m_resolution; i++) {
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);
            m_vertices.push_back(m_radius);

            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);
            m_vertices.push_back(m_radius);

            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);
            m_vertices.push_back(m_radius);

            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);
            m_vertices.push_back(m_radius);
        }
    }
    // Face 3
    for (unsigned int j = 0; j < m_resolution; j++) {
        for (unsigned int i = 0; i < m_resolution; i++) {
            m_vertices.push_back(m_radius);
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);

            m_vertices.push_back(m_radius);
            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);

            m_vertices.push_back(m_radius);
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);

            m_vertices.push_back(m_radius);
            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);
        }
    }
    // Face 4
    for (unsigned int j = 0; j < m_resolution; j++) {
        for (unsigned int i = 0; i < m_resolution; i++) {
            m_vertices.push_back(-m_radius);
            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);

            m_vertices.push_back(-m_radius);
            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);

            m_vertices.push_back(-m_radius);
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);

            m_vertices.push_back(-m_radius);
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(j * segment_width - m_radius);
        }
    }
    // Face 5
    for (unsigned int j = 0; j < m_resolution; j++) {
        for (unsigned int i = 0; i < m_resolution; i++) {
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(-m_radius);
            m_vertices.push_back(j * segment_width - m_radius);

            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(-m_radius);
            m_vertices.push_back(j * segment_width - m_radius);

            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(-m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);

            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(-m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);
        }
    }
    // Face 6
    for (unsigned int j = 0; j < m_resolution; j++) {
        for (unsigned int i = 0; i < m_resolution; i++) {
            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);

            m_vertices.push_back((i+1) * segment_width - m_radius);
            m_vertices.push_back(m_radius);
            m_vertices.push_back(j * segment_width - m_radius);

            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(m_radius);
            m_vertices.push_back((j+1) * segment_width - m_radius);
            
            m_vertices.push_back(i * segment_width - m_radius);
            m_vertices.push_back(m_radius);
            m_vertices.push_back(j * segment_width - m_radius);
        }
    }
}

void Planet::Render(Shader& shader, const VertexArray& va, const IndexBuffer& ib) {
    shader.Bind();
    va.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}

std::vector<float> Planet::GetVertices() {
    return m_vertices;
}