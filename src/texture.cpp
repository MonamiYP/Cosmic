#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path) : m_textureID(0), m_filepath(path), m_textureData(nullptr), 
    m_width(0), m_height(0), m_BPP(0) {
    stbi_set_flip_vertically_on_load(1);
    
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    m_textureData = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 0);

    if (m_textureData) {
        GLenum format;
        if (m_BPP == 1) {format = GL_RED;}
        else if (m_BPP == 3) {format = GL_RGB;}
        else {format = GL_RGBA;}
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(m_textureData);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_textureID);
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}