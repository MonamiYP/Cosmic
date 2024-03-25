#include "GenerateVertices.hpp"

std::vector<float> GenerateVertices::GetCubeVertices() {
    std::vector<float> cubeVertices = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f

        };
    return cubeVertices;
}

std::vector<float> GenerateVertices::GetSphereVertices(float radius, float resolution) {
    std::vector<float> sphereVertices;
    float segment_width = radius*2/resolution;
    for (unsigned int j = 0; j < resolution; j++) {
        // Face 1
        for (unsigned int i = 0; i < resolution; i++) {
            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);
            sphereVertices.push_back(-radius);

            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);
            sphereVertices.push_back(-radius);
            
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);
            sphereVertices.push_back(-radius);

            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);
            sphereVertices.push_back(-radius);
        }
    }
    // Face 2
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);
            sphereVertices.push_back(radius);

            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);
            sphereVertices.push_back(radius);

            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);
            sphereVertices.push_back(radius);

            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);
            sphereVertices.push_back(radius);
        }
    }
    // Face 3
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            sphereVertices.push_back(radius);
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);

            sphereVertices.push_back(radius);
            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);

            sphereVertices.push_back(radius);
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);

            sphereVertices.push_back(radius);
            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);
        }
    }
    // Face 4
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            sphereVertices.push_back(-radius);
            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);

            sphereVertices.push_back(-radius);
            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);

            sphereVertices.push_back(-radius);
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back((j+1) * segment_width - radius);

            sphereVertices.push_back(-radius);
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(j * segment_width - radius);
        }
    }
    // Face 5
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(-radius);
            sphereVertices.push_back(j * segment_width - radius);

            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(-radius);
            sphereVertices.push_back(j * segment_width - radius);

            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(-radius);
            sphereVertices.push_back((j+1) * segment_width - radius);

            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(-radius);
            sphereVertices.push_back((j+1) * segment_width - radius);
        }
    }
    // Face 6
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(radius);
            sphereVertices.push_back((j+1) * segment_width - radius);

            sphereVertices.push_back((i+1) * segment_width - radius);
            sphereVertices.push_back(radius);
            sphereVertices.push_back(j * segment_width - radius);

            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(radius);
            sphereVertices.push_back((j+1) * segment_width - radius);
            
            sphereVertices.push_back(i * segment_width - radius);
            sphereVertices.push_back(radius);
            sphereVertices.push_back(j * segment_width - radius);
        }
    }

    return sphereVertices;
}