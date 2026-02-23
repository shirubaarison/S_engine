#include "core/Renderer.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/errorReporting.h"

Renderer::Renderer(int width, int height) : m_width(width), m_height(height) {}
Renderer::~Renderer() {}

bool Renderer::init() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "GLAD initialization failed.\n";
    return false;
  }
  enableReportGlErrors();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, m_width, m_height);

  return true;
}

void Renderer::draw() {

}

void Renderer::render() {

}
