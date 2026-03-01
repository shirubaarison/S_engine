#include "resources/ResouceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;

Shader &ResourceManager::loadShader(const std::string &name, const char *vertexPath, const char *fragmentPath) {
  shaders[name] = Shader(vertexPath, fragmentPath);

  return shaders[name];
}

Shader &ResourceManager::getShader(const std::string &name) {
  return shaders[name];
}
