#pragma once


// GLEW DOIT être inclus AVANT tout autre header OpenGL
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>


class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    
    // Uniforms
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    
    GLuint GetProgramID() const { return m_Program; }
    
private:
    GLuint CompileShader(const std::string& source, GLenum type);
    std::string ReadFile(const std::string& filepath);
    GLint GetUniformLocation(const std::string& name);
    
    GLuint m_Program;
    std::unordered_map<std::string, GLint> m_UniformCache;
};