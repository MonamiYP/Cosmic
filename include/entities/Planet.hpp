#pragma once
#include "Requirements.hpp"

class Planet {
    public:
        Planet(int resolution, float diameter);
        ~Planet() {}

        void Render(Shader& shader, const VertexArray& va, const IndexBuffer& ib);
        std::vector<float> GetVertices();
        float GetRadius() { return m_radius; }
        int GetResolution() { return m_resolution; }
        void CreateMesh();
    private:
        std::vector<float> m_vertices;
        float m_radius;
        int m_resolution;
};