#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

class Shader {
    private:
        unsigned int m_shaderProgramID;
        std::unordered_map<std::string, int> m_uniformLocationCache;

    public:
        Shader() {};
        ~Shader() {};

        void Bind() const;
        void Unbind() const;

        unsigned int CompileShader(unsigned int type, const std::string& source);
        std::string ParseShader(const std::string& filepath);
        void CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

        int GetUniformLocation(const std::string& name);

        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);
        void SetVector3(const std::string& name, const glm::vec3& vector);
        void SetMatrix4(const std::string& name, const glm::mat4& matrix);
};