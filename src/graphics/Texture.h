#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <string>

class Texture {
public:
  Texture();
  Texture(const char *imagePath, GLuint slot, GLenum wrapping);
  ~Texture();

  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;

  Texture(Texture&& other) noexcept;
  Texture& operator=(Texture&& other) noexcept;
 
  void bind() const;
  void unbind() const;

  GLuint getId() const { return m_id; }
  const std::string& getPath() const { return m_path; }

private:
  GLuint m_id{0};
  GLuint m_unit{0};
  std::string m_path;
  unsigned int m_width{0}, m_height{0};
};

#endif // !TEXTURE_CLASS_H
