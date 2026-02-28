#include "graphics/Texture.h"
#include "resources/ResouceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader &ResourceManager::loadShader(const std::string &name, const char *vertexPath, const char *fragmentPath) {
  shaders[name] = Shader(vertexPath, fragmentPath);

  return shaders[name];
}

Shader &ResourceManager::getShader(const std::string &name) {
  return shaders[name];
}

Texture &ResourceManager::loadTexture(const std::string &name, const char *path) {
  // TODO: change wrapping ? and what about slot?
  textures[name] = Texture(path, 0, GL_REPEAT);

  return textures[name];
}

Texture &ResourceManager::getTexture(const std::string &name) {
  return textures[name];
}

void ResourceManager::clear() {
  // TODO
}
