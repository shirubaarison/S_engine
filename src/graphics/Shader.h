#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <iostream> // IWYU pragma: keep

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
  GLuint ID;
  
  Shader(const char *vertexSource, const char *fragmentSource);
  Shader &use();

  // utility
  void setFloat    (const char *name, float value) const;
  void setInteger  (const char *name, int value) const;
  void setVector2f (const char *name, float x, float y) const;
  void setVector2f (const char *name, const glm::vec2 &value) const;
  void setVector3f (const char *name, float x, float y, float z) const;
  void setVector3f (const char *name, const glm::vec3 &value) const;
};

#endif // !SHADER_CLASS_H
