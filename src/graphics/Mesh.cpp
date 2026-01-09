#include <graphics/Mesh.h>
#include <spdlog/spdlog.h>
Mesh::Mesh()
{
    spdlog::info("Mesh Contrusctor called");

}
Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) :m_Vertices(vertices), m_Indices(indices), m_VAO(0), m_VBO(0), m_EBO(0)
{
    SetupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArray(1, &m_VAO);
    glDeleteBuffer(1, &m_VBO);
    glDeleteBuffer(1, &m_EBO);
}

void Mesh::SetupMesh()
{
    // Generate Buffer
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArrays(m_VAO);

    // VBO

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
    
    // EBO - Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(uint32_t), m_Indices.data(), GL_STATIC_DRAW);

    // Vertex attributes
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3 GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void)* offsetof(Vertex, texCoord))

    glBindVertexArrays(0);

    spdlog("Mesh created: {} vertices, {} indices", m_Vertices.size(), m_Indices.size());

}

Mesh::ScaleMesh(float scaleFactor)
{
}


Mesh::Draw()
{
    glBindVertexArray(m_VAO);
    glDrawElement(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

