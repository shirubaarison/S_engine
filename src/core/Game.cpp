#include <iostream>

#include "core/Game.h"
#include "core/SpriteRenderer.h"
#include "resources/ResouceManager.h"
#include "utils/debug.h"

#define FLOOR_Y 0

Game::Game() {}

bool Game::init() {
  window = new Window();

  if (!window->init())
    return false;

  input = new Input();
  if (!input->init(*window))
    return false;

  loadAssets();

  renderer = new SpriteRenderer(ResourceManager::getShader("default"));
  if (!renderer->init())
    return false;

  player = new Player(input,
                      glm::vec2(window->getWidth() / 2 ,
                                window->getHeight() / 2));

#ifdef DEBUG_MESSAGES
  std::cout << "[Game] initialization completed successfully!" << std::endl;
#endif

  return true;
}

void Game::shutdown() {
  // TODO
}

void Game::render() {

  glm::vec2 playerPos = player->getPos();

  renderer->drawSprite(ResourceManager::getTexture("player"), playerPos,
                       glm::vec2(500.0f, 500.0f));
}

void Game::run() {
  if (window == nullptr || renderer == nullptr)
    return;

  float deltaTime = 0.0f;
  float mLastFrame = 0.0f;

  while (!window->shouldClose()) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    renderer->render();

    render();

    player->update(deltaTime);

    window->update();
  }
}

void Game::handlePlayerCollision() {
  // todo
}

void Game::loadAssets() {
  ResourceManager::loadShader("default", "shaders/default.vert",
                              "shaders/default.frag");
  ResourceManager::loadTexture("player", "assets/player.png");

#ifdef DEBUG_MESSAGES
  std::cout << "[Game] assets loaded" << std::endl;
#endif
}
