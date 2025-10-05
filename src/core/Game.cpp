#include <iostream>

#include "core/Game.h"
#include "utils/debug.h"

Game::Game() {}

bool Game::init() {
  window = new Window();

  if (!window->init()) return false;

  renderer = new Renderer();
  if (!renderer->init()) return false;

  #ifdef DEBUG_MESSAGES 
    std::cout << "[Game] initialization completed successfully!";
  #endif

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
