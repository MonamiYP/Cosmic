#pragma once
#include <vector>

namespace GenerateVertices {
    extern std::vector<float> GetCubeVertices();
    extern std::vector<float> GetSphereVertices(float radius, float resolution);
}