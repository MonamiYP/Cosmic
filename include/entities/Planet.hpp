#pragma once
#include "Requirements.hpp"

class Planet {
    public:
        Planet();
        ~Planet() {}

        void Render(Shader& shader, const VertexArray& va, const IndexBuffer& ib);
        std::vector<float> GetVertices();
        std::vector<unsigned int> GetIndices();
        void CreateMesh(float width, int resolution);
    private:
        unsigned int m_VBO, m_VAO, m_IBO;
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;
};