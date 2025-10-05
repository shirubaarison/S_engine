#include <iostream>

#include "utils/common.h"
#include "core/Renderer.h"

#include "utils/debug.h"

#define DEFAULT_BACKGROUND 0.15f, 0.15f, 0.15f, 1.0f

Renderer::Renderer() {}

bool Renderer::init() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "GLAD initialization failed.\n";
    return false;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  #ifdef DEBUG_MESSAGES
    std::cout << "[Renderer] sucessfully initialized.\n";
  #endif

  return true;
}

void Renderer::render() {
  glClearColor(DEFAULT_BACKGROUND);

  glClear(GL_COLOR_BUFFER_BIT);
}
