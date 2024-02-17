#include "Planet.hpp"

Planet::Planet() {
}

void Planet::CreateMesh(float width, int resolution) {
    float segment_width = width/resolution;
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            m_vertices.push_back(i * segment_width - width/2);
            m_vertices.push_back(j * segment_width - width/2);
            m_vertices.push_back(-width/2);

            m_vertices.push_back((i+1) * segment_width - width/2);
            m_vertices.push_back(j * segment_width - width/2);
            m_vertices.push_back(-width/2);

            m_vertices.push_back(i * segment_width - width/2);
            m_vertices.push_back((j+1) * segment_width - width/2);
            m_vertices.push_back(-width/2);

            m_vertices.push_back((i+1) * segment_width - width/2);
            m_vertices.push_back((j+1) * segment_width - width/2);
            m_vertices.push_back(-width/2);
        }
    }
    
    for (int j = 0; j < (resolution-1); j++) {
        for (int i = 0; i < (resolution-1); i++) {
            m_indices.push_back(i+(j*resolution));
            m_indices.push_back(i+resolution+(j*resolution));
            m_indices.push_back(i+resolution+1+(j*resolution));

            m_indices.push_back(i+(j*resolution));
            m_indices.push_back(i+1+(j*resolution));
            m_indices.push_back(i+resolution+1+(j*resolution));
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

std::vector<unsigned int> Planet::GetIndices() {
    return m_indices;
}