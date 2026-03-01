#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "graphics/Shader.h"
#include <map>

class ResourceManager {
public:
  ResourceManager() = delete;

  static Shader &loadShader(const std::string &name, const char *vertexPath, const char *fragmentPath);
  static Shader &getShader(const std::string &name);

  void clear();
private:
  static std::map<std::string, Shader> shaders;
};

#endif // !RESOURCE_MANAGER_H
