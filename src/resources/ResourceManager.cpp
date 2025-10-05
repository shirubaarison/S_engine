#include "graphics/Texture.h"
#include "resources/ResouceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader &ResourceManager::loadShader(const std::string &name, const char *vertexPath, const char *fragmentPath) {
  shaders[name] = Shader(vertexPath, fragmentPath);

  return shaders[name];
}

Shader &ResourceManager::getShader(const std::string &name) {
  return shaders[name];
}

Texture2D &ResourceManager::loadTexture(const std::string &name, const char *path) {
  // TODO: change wrapping ? and what about slot?
  textures[name] = Texture2D(path, 0, GL_REPEAT);

  return textures[name];
}

Texture2D &ResourceManager::getTexture(const std::string &name) {
  return textures[name];
}

void ResourceManager::clear() {
  // TODO
}
