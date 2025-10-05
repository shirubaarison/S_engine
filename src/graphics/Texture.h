#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <iostream> // IWYU pragma: keep

class Texture2D {
  unsigned int width, height;
public:
  GLuint ID;
  GLuint unit;
  std::string path;
 
  Texture2D(const char *imagePath, GLuint slot, GLenum wrapping);
 
  void generate();
  void bind() const;
  void unbind() const;

};

#endif // !TEXTURE_CLASS_H
