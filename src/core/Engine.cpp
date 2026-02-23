#include <iostream>
#include "resources/ResouceManager.h"
#include "core/Engine.h"
#include "core/Renderer.h"
#include "utils/debug.h"

Engine::Engine() {}
Engine::~Engine() { shutdown(); }

bool Engine::init() {
  m_window = std::make_unique<Window>();

  if (!m_window->init())
    return false;

  m_renderer = std::make_unique<Renderer>(m_window->getWidth(), m_window->getHeight());
  if (!m_renderer->init())
    return false;

  m_input = std::make_unique<Input>();
  if (!m_input->init(m_window->getWindow()))
    return false;

  loadAssets();

#ifdef DEBUG_MESSAGES
  std::cout << "[Engine] initialization completed successfully!" << std::endl;
#endif

  return true;
}

void Engine::shutdown() {
  // TODO
}

void Engine::update(float deltaTime) {
  (void)deltaTime;
  if (m_input->isKeyPressed(GLFW_KEY_F)) {
    m_window->toggleFullScreen();
  }
}

void Engine::render() {
}

void Engine::handleInput(double deltaTime) {
}

void Engine::run() {
  float deltaTime = 0.0f;
  float mLastFrame = 0.0f;

  while (!m_window->shouldClose()) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    m_renderer->render();

    handleInput(deltaTime);
    update(deltaTime);
    render();

    m_window->update();
  }
}

void Engine::loadAssets() {
  ResourceManager::loadShader("default", "shaders/default.vert", "shaders/default.frag");

#ifdef DEBUG_MESSAGES
  std::cout << "[Engine] assets loaded" << std::endl;
#endif
}
