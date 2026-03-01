#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "graphics/Model.h"
#include "graphics/Shader.h"
#include <map>
#include <memory>

class ResourceManager {
public:
  ResourceManager() = delete;

  static Shader &loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath);
  static Shader &getShader(const std::string& name) { return shaders[name]; }

  static std::shared_ptr<Model> loadModel(const std::string& name, const std::string& path);
  static std::shared_ptr<Model> getModel(const std::string& name) { return models[name]; }

private:
  static std::map<std::string, Shader> shaders;
  static std::map<std::string, std::shared_ptr<Model>> models;
};

#endif // !RESOURCE_MANAGER_H
