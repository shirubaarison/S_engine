#include <iostream>
#include <stb_image.h>
#include <stdexcept>

#include "graphics/Texture.h"
#include "utils/debug.h"

Texture::Texture() : m_id{0}, m_unit{0}, m_width{0}, m_height{0} {}

Texture::Texture(const char *imagePath, const char *type, GLenum wrapping)
    : m_path(imagePath),
      m_type(type)
{
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

  if (data == nullptr) {
    std::cerr << "[Texture] Error loading texture: '" << imagePath << ".\n";
    throw std::runtime_error("Failed to load texture");
  }

  glGenTextures(1, &m_id);
  glActiveTexture(GL_TEXTURE0 + m_unit);

  GLenum format;
  switch (nrChannels) {
  case 1:
    format = GL_RED;
    break;
  case 3:
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  default:
    std::cerr
        << "[Texture] error when trying to define which format is the texture '"
        << imagePath << "'.\n'";
      if (data)
        stbi_image_free(data);
    throw std::runtime_error("Invalid texture format");
  }

  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  m_width = width;
  m_height = height;

  if (data)
    stbi_image_free(data);

#ifdef DEBUG_MESSAGES
  std::cout << "[Texture] id: " << m_id << " loaded '" << imagePath
            << "' successfully. Info: " << m_width << "x" << m_height
            << " channels: " << nrChannels << "." << std::endl;
#endif
}

Texture::~Texture()
{
  if (m_id != 0) {
    glDeleteTextures(1, &m_id);
    m_id = 0;
  }
}

void Texture::bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }

void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

Texture::Texture(Texture&& other) noexcept
  : m_id{other.m_id},
    m_path{std::move(other.m_path)},
    m_width{other.m_width},
    m_height{other.m_height}
{
  other.m_id = 0;
  other.m_width = 0;
  other.m_height = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
  if (this != &other) {
    if (m_id != 0)
      glDeleteTextures(1, &m_id);

    m_id = other.m_id;
    m_path = std::move(other.m_path);
    m_width = other.m_width;
    m_height = other.m_height;

    other.m_id = 0;
  }

  return *this;
}
