#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "graphics/Camera.h"
#include "graphics/Model.h"
#include "graphics/Shader.h"

class Renderer {
public:
  Renderer(int width, int height);
  ~Renderer();

  bool init();

  void draw();
  void drawModel(const Model& model, Shader& shader, const Camera& camera, const glm::mat4& modelMatrix);
  void render();

private:
  int m_width;
  int m_height;

  int m_aspectRatio;
};

#endif // !RENDERER_CLASS_H
