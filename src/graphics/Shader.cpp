#include "graphics/Shader.h"
#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath):  m_Program(0)
{

    std::string vertexSource = ReadFile(vertexPath);
    std::string fragmentSource = ReadFile(fragmentPath);

    GLuint vertexShader = CompileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Link prograM
    m_Program = glCreateProgram();
    glAttachShader(m_Program, vertexShader);
    glAttachShader(m_Program, fragmentShader);

    glLinkProgram(m_Program);

    // get lfinkled eerror
    GLint success;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
        spdlog::error("Shader linking failed: {}", infoLog);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}


GLuint Shader::CompileShader(const std::string& source, GLenum type)
{

    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // CHeckl compilation
    GLint succes;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
    if(!succes)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        spdlog::error("Shader compilation fdailes: {}", infoLog);

    }
    return shader;
}

std::string Shader::ReadFile(const std::string& filePath)
{

    std::string src;
    std::ifstream(filePath)
    if(!file.is_open()) {
        spdlog::error("Unable to loads file path: {}", filePath);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    src= buffer.str();
    return src;
}