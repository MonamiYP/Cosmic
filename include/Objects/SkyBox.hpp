#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include <vector>
#include <string>
#include <iostream>

class SkyBox {
    public:
        SkyBox();
        ~SkyBox() {}
    
        unsigned int loadSkyBox(std::vector<std::string> faces);
};