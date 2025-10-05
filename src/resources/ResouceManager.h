#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <map>

class ResourceManager {
public:
  static std::map<std::string, Shader> shaders;
  static std::map<std::string, Texture2D> textures;

  ResourceManager() = delete;

  static Shader &loadShader(const std::string &name, const char *vertexPath, const char *fragmentPath);
  static Shader &getShader(const std::string &name);

  static Texture2D &loadTexture(const std::string &name, const char *path);
  static Texture2D &getTexture(const std::string &name);

  void clear();
};

#endif // !RESOURCE_MANAGER_H
