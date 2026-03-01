#include "graphics/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int materialIndex)
  : m_vertices(vertices),
    m_indices(indices),
    m_materialIndex(materialIndex)
{
  setupMesh();
}

Mesh::~Mesh()
{
  if (m_vao != 0) {
    glDeleteVertexArrays(1, &m_vao);
  }

  if (m_vbo != 0) {
    glDeleteBuffers(1, &m_vbo);
  }

  if (m_ebo != 0) {
    glDeleteBuffers(1, &m_ebo);
  }
}

void Mesh::setupMesh()
{
  // generate and bind VAO
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // generate VBO
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

  // generate EBO
  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

  // link attribs
  // location 0 = position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  // location 1 = normals
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  // location 2 = texCoords
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw() const
{
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

Mesh::Mesh(Mesh&& other) noexcept
  : m_vao{other.m_vao},
    m_vbo{other.m_vbo},
    m_ebo{other.m_ebo},
    m_vertices{std::move(other.m_vertices)},
    m_indices{std::move(other.m_indices)}
{
  other.m_vao = 0;
  other.m_vbo = 0;
  other.m_ebo = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
  if (this != &other) {
    if (m_vao != 0)
      glDeleteVertexArrays(1, &m_vao);
    if (m_vbo !=  0)
      glDeleteBuffers(1, &m_vbo);
    if (m_ebo != 0)
      glDeleteBuffers(1, &m_ebo);

    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ebo = other.m_ebo;
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);

    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_ebo = 0;
  }

  return *this;
}
