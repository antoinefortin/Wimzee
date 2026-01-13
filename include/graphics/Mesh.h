#pragma once


#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>
#include <cstdint>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    
    Vertex(const glm::vec3& pos, const glm::vec3& norm, const glm::vec2& uv)
        : position(pos), normal(norm), texCoord(uv) {}
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    ~Mesh();
    
    void Draw();
    
    const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
    const std::vector<uint32_t>& GetIndices() const { return m_Indices; }
    
private:
    void SetupMesh();
    
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
    
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};
