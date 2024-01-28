#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_arrayID));
    GLCall(glBindVertexArray(m_arrayID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_arrayID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    Bind();
    vb.Bind();

    const auto& attributes = layout.GetAttributes();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); i++) {
        const auto& attribute = attributes[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, attribute.size, attribute.type, attribute.normalised, layout.GetStride(), (void*)(size_t)offset));
        offset += attribute.size * sizeof(GLfloat);
    }
}

void VertexArray::Bind() {
    GLCall(glBindVertexArray(m_arrayID));
}

void VertexArray::Unbind() {
    GLCall(glBindVertexArray(0));
}