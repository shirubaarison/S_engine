#include <iostream>

#include "core/Game.h"
#include "core/SpriteRenderer.h"
#include "resources/ResouceManager.h"
#include "utils/debug.h"

Game::Game() {}

bool Game::init() {
  window = new Window();

  if (!window->init()) return false;

  input = new Input();
  if (!input->init(*window)) return false;

  loadAssets();

  renderer = new SpriteRenderer(ResourceManager::getShader("default"));
  if (!renderer->init()) return false;

#ifdef DEBUG_MESSAGES 
  std::cout << "[Game] initialization completed successfully!" << std::endl;
#endif

  return true;
}

void Game::shutdown() {
  // TODO
}

void Game::render() {
  renderer->drawSprite(ResourceManager::getTexture("player"), 
                       glm::vec2(500.0f, 500.0f),
                       glm::vec2(200.0f, 200.0f));
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
  ResourceManager::loadTexture("player", "assets/player.png");

#ifdef DEBUG_MESSAGES 
  std::cout << "[Game] assets loaded" << std::endl;
#endif
}
