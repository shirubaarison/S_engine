#include "graphics/Model.h"
#include "assimp/types.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <memory>
#include <stdexcept>
#include <iostream>


Model::Model(const std::string& path)
{
  loadModel(path);
}

Model::~Model()
{

}

void Model::draw(Shader& shader) const
{
  shader.use();

  for (const auto& mesh : m_meshes) {
    // get material
    unsigned int matIndex = mesh.getMaterialIndex();

    if (matIndex < m_materials.size()) {
      const Material& mat = m_materials[matIndex];

      if (mat.diffuseTexIndex >= 0 && static_cast<size_t>(mat.diffuseTexIndex) < m_textures.size()) {
        glActiveTexture(GL_TEXTURE0);
        m_textures[mat.diffuseTexIndex]->bind();
        shader.setInteger("texture_diffuse", 0);
        shader.setInteger("useDiffuseTexture", 1);
      } else {
        shader.setInteger("useDiffuseTexture", 0);
      }

      if (mat.specularTexIndex >= 0 && static_cast<size_t>(mat.specularTexIndex) < m_textures.size()) {
        glActiveTexture(GL_TEXTURE1);
        m_textures[mat.specularTexIndex]->bind();
        shader.setInteger("texture_specular", 1);
        shader.setInteger("useSpecularTexture", 1);
      } else {
        shader.setInteger("useSpecularTexture", 0);
      }

      shader.setVector3f("material.ambient", mat.ambientColor);
      shader.setVector3f("material.diffuse", mat.diffuseColor);
      shader.setVector3f("material.specular", mat.specularColor);
      shader.setFloat("material.shininess", mat.shininess);
    }

    mesh.draw();
  }
}

void Model::loadModel(const std::string& path)
{
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    throw std::runtime_error("Error loading model.");
  }

  m_directory = path.substr(0, path.find_last_of('/'));

  processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
  for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_meshes.push_back(processMesh(mesh, scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; ++i) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;

    vertex.position = glm::vec3{
      mesh->mVertices[i].x,
      mesh->mVertices[i].y,
      mesh->mVertices[i].z
    };

    if (mesh->HasNormals()) {
      vertex.normal = glm::vec3{
        mesh->mNormals[i].x,
        mesh->mNormals[i].y,
        mesh->mNormals[i].z
      };
    } else {
      vertex.normal = glm::vec3{0.0f, 1.0f, 0.0f};
    }

    if (mesh->mTextureCoords[0]) {
      vertex.texCoords = glm::vec2{
        mesh->mTextureCoords[0][i].x,
        mesh->mTextureCoords[0][i].y
      };
    } else {
      vertex.texCoords = glm::vec2{0.0f, 0.0f};
    }

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; ++j) {
      indices.push_back(face.mIndices[j]);
    }
  }

  unsigned int materialIndex{0};
  if (mesh->mMaterialIndex < scene->mNumMaterials) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    materialIndex = loadMaterial(material);
  }

  return Mesh(vertices, indices, materialIndex);
}

unsigned int Model::loadMaterial(aiMaterial *mat)
{
  Material material;

  // diffuse tex
  if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
    aiString texPath;
    mat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath);
    std::string fullPath = m_directory + "/" + std::string(texPath.C_Str());

    auto texture = loadTexture(fullPath, "diffuse");
    if (texture) {
      material.diffuseTexIndex = static_cast<int>(m_textures.size());
      // std::cout << "diffuseTexIndex for " << texPath.C_Str() << " is " << material.diffuseTexIndex << std::endl;
      m_textures.push_back(texture);
    }
  }

  // specular tex
  if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0) {
    aiString texPath;
    mat->GetTexture(aiTextureType_SPECULAR, 0, &texPath);
    std::string fullPath = m_directory + "/" + std::string(texPath.C_Str());

    auto texture = loadTexture(fullPath, "specular");
    if (texture) {
      material.specularTexIndex = static_cast<int>(m_textures.size());
      m_textures.push_back(texture);
    }
  }

  // colors
  aiColor3D color;
  if (mat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS) {
    material.ambientColor = glm::vec3{color.r, color.g, color.b};
  }

  if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
    material.diffuseColor = glm::vec3{color.r, color.g, color.b};
  }

  if (mat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS) {
    material.specularColor = glm::vec3{color.r, color.g, color.b};
  }

  float shininess;
  if (mat->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
    material.shininess = shininess;
  }

  m_materials.push_back(material);

  return m_materials.size() - 1;
}

std::shared_ptr<Texture> Model::loadTexture(const std::string& path, const std::string& type)
{
  // it is cached?
  for (const auto& tex : m_textures) {
    if (tex->getPath() == path) {
      std::cout << "'" << path << "' already cached." << std::endl;
      return tex;
    }
  }

  try {
    std::cout << "loading '" << path << "'." << std::endl;
    auto texture = std::make_shared<Texture>(
      path.c_str(),
      type.c_str(),
      GL_REPEAT
    );

    return texture;
  } catch (const std::exception& e) {
    std::cerr << "Failed to load texture: " << path << " - " << e.what() << std::endl;
    return nullptr;
  }
}
