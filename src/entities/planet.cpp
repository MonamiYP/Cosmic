#include "Planet.hpp"

Planet::Planet() {
}

void Planet::CreateMesh(float diameter, int resolution) {
    float segment_width = diameter/resolution;
    for (unsigned int j = 0; j < resolution; j++) {
        // Face 1
        for (unsigned int i = 0; i < resolution; i++) {
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);

            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);
        }
    }
    // Face 2
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);

            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);
        }
    }
    // Face 3
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            m_vertices.push_back(diameter/2);
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back(diameter/2);
            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back(diameter/2);
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);

            m_vertices.push_back(diameter/2);
            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
        }
    }
    // Face 4
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            m_vertices.push_back(-diameter/2);
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back(-diameter/2);
            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back(-diameter/2);
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);

            m_vertices.push_back(-diameter/2);
            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
        }
    }
    // Face 5
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(-diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
        }
    }
    // Face 6
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);
            m_vertices.push_back(j * segment_width - diameter/2);

            m_vertices.push_back(i * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);

            m_vertices.push_back((i+1) * segment_width - diameter/2);
            m_vertices.push_back(diameter/2);
            m_vertices.push_back((j+1) * segment_width - diameter/2);
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