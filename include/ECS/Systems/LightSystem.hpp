#pragma once

#include "Requirements.hpp"
#include "RequirementsECS.hpp"

#include "VertexArray.hpp"
#include "Shader.hpp"

#include "Engine.hpp"

class LightSystem : public System {
    public:
        void Init();
        void SetupShaderLights(Shader* shader);
    private:
};