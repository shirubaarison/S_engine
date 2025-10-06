#include <glm/ext/vector_float2.hpp>
#include <algorithm>
#include <cstdlib>

#include "game/Player.h"
#include "utils/debug.h"

#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 64

#define MAX_MOVE_SPEED 1000.0f

Player::Player(Input *input, glm::vec2 pos)
    : input(input), baseSpeed(5000.0f), pos(pos), velocity(glm::vec2(0, 0)),
      width(PLAYER_WIDTH), height(PLAYER_HEIGHT) {
#ifdef DEBUG_MESSAGES 
  std::cout << "[Player] initialized successfully." << std::endl;
#endif
}

void Player::update(float deltaTime) {
  handleKeyboardInput(deltaTime);

  pos.x += velocity.x * deltaTime;
  pos.y += velocity.y * deltaTime;
}

void Player::handleKeyboardInput(float deltaTime) {
  float acceleration = baseSpeed * deltaTime;

  if (input->isKeyPressed(GLFW_KEY_LEFT)) {
    velocity.x -= acceleration;
  }

  if (input->isKeyPressed(GLFW_KEY_RIGHT)) {
    velocity.x += acceleration;
  }

  if (input->isKeyPressed(GLFW_KEY_UP)) {
    velocity.y -= acceleration;
  }

  if (input->isKeyPressed(GLFW_KEY_DOWN)) {
    velocity.y += acceleration;
  }

  if (!input->isKeyPressed(GLFW_KEY_LEFT) &&
      !input->isKeyPressed(GLFW_KEY_RIGHT)) {
    velocity.x *= 0.2f;

    if (std::abs(velocity.x) < 0.1f)
      velocity.x = 0.0f;
  }

  if (!input->isKeyPressed(GLFW_KEY_UP) &&
      !input->isKeyPressed(GLFW_KEY_DOWN)) {
    velocity.y *= 0.2f;

    if (std::abs(velocity.y) < 0.1f)
      velocity.y = 0.0f;
  }

  velocity.x = std::clamp(velocity.x, -MAX_MOVE_SPEED, MAX_MOVE_SPEED);
  velocity.y = std::clamp(velocity.y, -MAX_MOVE_SPEED, MAX_MOVE_SPEED);
}

glm::vec2 Player::getPos() const { return pos; }

glm::vec2 Player::getVelocity() const { return velocity; }

void Player::setPos(glm::vec2 pos) { this->pos = pos; }

int Player::getWidth() const { return width; }

int Player::getHeight() const { return height; }
