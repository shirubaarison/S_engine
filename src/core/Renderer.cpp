#include "core/Renderer.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/errorReporting.h"

Renderer::Renderer(int width, int height) : m_width(width), m_height(height)
{
  m_aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);
}

Renderer::~Renderer() {}

bool Renderer::init()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "GLAD initialization failed.\n";
    return false;
  }
  enableReportGlErrors();

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, m_width, m_height);

  return true;
}

void Renderer::draw()
{

}

void Renderer::drawModel(const Model& model, Shader& shader, const Camera& camera, const glm::mat4& modelMatrix)
{
  shader.use();

  shader.setMatrix4("model", modelMatrix);
  shader.setMatrix4("view", camera.getViewMatrix());
  shader.setMatrix4("projection", camera.getProjectionMatrix(m_aspectRatio));

  shader.setVector3f("lightPos", glm::vec3(2.0f, 4.0f, 3.0f));
  shader.setVector4f("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  shader.setVector3f("camPos", camera.getPosition());

  model.draw(shader);
}

void Renderer::render()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
