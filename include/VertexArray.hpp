#pragma once

#include <glad/glad.h>
#include "VertexBuffer.hpp"

class VertexBufferLayout;

class VertexArray {
    private:
        unsigned int m_arrayID;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void Bind();
        void Unbind();
};