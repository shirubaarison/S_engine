#include "graphics/Texture.h"
#include "stb_image.h"

#include "utils/debug.h"

Texture2D::Texture2D(const char *imagePath, GLuint slot, GLenum wrapping) : unit(slot), path(imagePath) {
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

  if (data == nullptr) {
    std::cerr << "[Texture2D] Error loading texture: '" << imagePath << "'.\n";
    return;
  }

  glGenTextures(1, &this->ID);
  glActiveTexture(GL_TEXTURE0 + unit);
  
  GLenum format;
  switch (nrChannels) {
    case 1:
      format = GL_RED; break;
    case 3:
      format = GL_RGB; break;
    case 4:
      format = GL_RGBA; break;
    default:
      std::cerr << "[Texture] error when trying to define which format is the texture '" << imagePath << "'.\n'";
      return;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_INT, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  this->width = width;
  this->height = height;

  if (data)
    stbi_image_free(data);

#ifdef DEBUG_MESSAGES 
  std::cout << "[Texture] loaded '" << imagePath << "' successfully. Info: " << width << "x" << height << " channels: " << nrChannels << ".\n";
#endif
}

void Texture2D::bind() const {
  glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture2D::unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}
