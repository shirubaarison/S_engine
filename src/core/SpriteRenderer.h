#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/fwd.hpp"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

class SpriteRenderer {
  Shader shader;
  GLuint quadVAO;
  
  void initRenderData();
public:
  SpriteRenderer(Shader &shader);
  ~SpriteRenderer();

  void drawSprite(Texture2D &texture,
                  glm::vec2 position,
                  glm::vec2 size = glm::vec2(10.0f, 10.0f),
                  float rotate = 0.0f,
                  glm::vec3 color = glm::vec3(1.0f)
                  );

  bool init();
  void render();
};

#endif // !SPRITE_RENDERER_H
