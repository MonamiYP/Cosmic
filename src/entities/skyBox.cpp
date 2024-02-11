#include "SkyBox.hpp"

SkyBox::SkyBox() {

}

unsigned int SkyBox::loadSkyBox(std::vector<std::string> faces) {
    stbi_set_flip_vertically_on_load(0);
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    int width, height, nrChannels;
    for(unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* skyboxData = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (skyboxData) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, skyboxData);
        } else { std::cout << "Failed to load cube map texture" << std::endl; }
        stbi_image_free(skyboxData);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}