#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include "graphics/Shader.h"
#include "resources/ResouceManager.h"
#include "utils/common.h"
#include "utils/debug.h"
#include "core/SpriteRenderer.h"

#define DEFAULT_BACKGROUND 0.15f, 0.15f, 0.15f, 1.0f

SpriteRenderer::SpriteRenderer(Shader &shader) {
  this->shader = shader;

  initRenderData();
}

void SpriteRenderer::initRenderData() {
  GLuint VBO;

  float vertices[] = {
    // pos      // tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void SpriteRenderer::drawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
  this->shader.use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  this->shader.setMatrix4("model", model);
  this->shader.setVector3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}


bool SpriteRenderer::init() {
  // config shaders 
  ResourceManager::getShader("default").use();
 
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.0f, -1.0f, 1.0f);
  ResourceManager::getShader("default").setInteger("image", 0);
  ResourceManager::getShader("default").setMatrix4("projection", projection);

  #ifdef DEBUG_MESSAGES
    std::cout << "[Renderer] sucessfully initialized." << std::endl;
  #endif

  return true;
}

void SpriteRenderer::render() {
  glClearColor(DEFAULT_BACKGROUND);

  glClear(GL_COLOR_BUFFER_BIT);
}
