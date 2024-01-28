#include "Shader.hpp"

void Shader::Bind() const {
    glUseProgram(m_shaderProgramID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    m_shaderProgramID = shaderProgram;
}

std::string Shader::ParseShader(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string str;
    std::string content;

    while (std::getline(file, str)) {
        content.append(str + "\n");
    }

    if (content.empty()) {
        std::cout << "ERROR::SHADER::CANNOT_FIND_FILE" << std::endl;
    }

    return content;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // Error handling
    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:"<<
        (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
        <<":COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}