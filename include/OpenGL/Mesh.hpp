#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

#include "Shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct MeshTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
    private:
        unsigned int m_VBO, m_VAO, m_IBO;

        std::vector<Vertex>       m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<MeshTexture>      m_textures;

        void SetupMesh();
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshTexture>& textures);
        ~Mesh() {};
        void Draw(Shader &shader);
};