#include <iostream>

#include "core/Game.h"
#include "resources/ResouceManager.h"
#include "utils/debug.h"

Game::Game() {}

bool Game::init() {
  window = new Window();

  if (!window->init()) return false;

  input = new Input();
  if (!input->init(*window)) return false;

  renderer = new Renderer();
  if (!renderer->init()) return false;

  #ifdef DEBUG_MESSAGES 
    std::cout << "[Game] initialization completed successfully!" << std::endl;
  #endif
  
  loadAssets();

  return true;
}

void Game::shutdown() {
  // TODO
}

void Game::render() {
  // TODO
}

void Game::run() {
  if (window == nullptr || renderer == nullptr) return;

  // float deltaTime = 0.0f;
  // float mLastFrame = 0.0f;

  while (!window->shouldClose()) {
    renderer->render();

    render();

    window->update();
  }
}

void Game::loadAssets() {
  ResourceManager::loadShader("default", "shaders/default.vert", "shaders/default.frag");
}
