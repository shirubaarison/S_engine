#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

class Mesh {
public:
  Mesh(const std::vector<Vertex>& vertices,
       const std::vector<unsigned int>& indices,
       unsigned int materialIndex = 0);
  ~Mesh();

  // delete copy
  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;

  // allow move
  Mesh(Mesh&& other) noexcept;
  Mesh& operator=(Mesh&& other) noexcept;

  void draw() const;
  unsigned int getMaterialIndex() const { return m_materialIndex; }
private:
  GLuint m_vao{0};
  GLuint m_vbo{0};
  GLuint m_ebo{0};

  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;

  unsigned int m_materialIndex{0};

  void setupMesh();
};

#endif // !MESH_CLASS_H
