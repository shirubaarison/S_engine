#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
  Renderer();
  
  bool init();
  void render();
};

#endif // !RENDERER_H
