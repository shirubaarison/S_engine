#include "resources/ResourceManager.h"
#include <memory>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, std::shared_ptr<Model>> ResourceManager::models;

Shader& ResourceManager::loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath)
{
  shaders[name] = Shader(vertexPath, fragmentPath);

  return shaders[name];
}

std::shared_ptr<Model> ResourceManager::loadModel(const std::string& name, const std::string& path)
{
  models[name] = std::make_shared<Model>(path);

  return models[name];
}
