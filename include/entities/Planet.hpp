#pragma once
#include "Requirements.hpp"

class Planet {
    public:
        Planet();
        ~Planet() {}

        void Render(Shader& shader, const VertexArray& va, const IndexBuffer& ib);
        std::vector<float> GetVertices();
        float GetRadius() { return m_radius; }
        void CreateMesh(float width, int resolution);
    private:
        std::vector<float> m_vertices;
        float m_radius;
};