#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "assimp/material.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include <memory>
#include <string>
#include <vector>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

struct Material {
  int diffuseTexIndex{-1};
  int specularTexIndex{-1};

  glm::vec3 ambientColor{1.0f};
  glm::vec3 diffuseColor{1.0f};
  glm::vec3 specularColor{1.0f};

  float shininess{32.0f};
};

class Model {
public:
  Model(const std::string& path);
  ~Model();

  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;

  Model(Model&& other) noexcept = default;
  Model& operator=(Model&& other) noexcept = default;

  void draw(Shader& shader) const;

private:
  std::vector<Mesh> m_meshes;
  std::vector<std::shared_ptr<Texture>> m_textures;
  std::vector<Material> m_materials;

  std::string m_directory;

  void loadModel(const std::string& path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);

  unsigned int loadMaterial(aiMaterial *mat);
  std::shared_ptr<Texture> loadTexture(const std::string& path, const std::string& type);
};

#endif // !MODEL_CLASS_H
