#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <iostream> // IWYU pragma: keep

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
  Shader();
  Shader(const char *vertexPath, const char *fragmentPath);

  Shader &use();

  // utility
  void setFloat    (const char *name, float value) const;
  void setInteger  (const char *name, int value) const;
  void setVector2f (const char *name, float x, float y) const;
  void setVector2f (const char *name, const glm::vec2 &value) const;
  void setVector3f (const char *name, float x, float y, float z) const;
  void setVector3f (const char *name, const glm::vec3 &value) const;
  void setVector4f (const char *name, const glm::vec4 &value) const;
  void setVector4f (const char *name, float x, float y, float z, float w) const;
  void setMatrix4  (const char *name, const glm::mat4 &matrix) const;
private:
  GLuint m_id;
};

#endif // !SHADER_CLASS_H
