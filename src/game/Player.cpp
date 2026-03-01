#include <cmath>
#include <glm/ext/vector_float2.hpp>
#include <memory>

#include "game/Player.h"
#include "core/GameObject.h"

Player::Player(Input* input, std::shared_ptr<Model> model, glm::vec3 startPos)
  : GameObject(model, startPos), m_input(input) {}

void Player::update(float deltaTime)
{
  checkGround();
  handleInput(deltaTime);
  applyPhysics(deltaTime);
}

void Player::handleInput(float deltaTime)
{
  glm::vec3 forward(
    sin(m_rotation.y),
    0.0f,
    cos(m_rotation.y)
  );

  if (m_input->isKeyPressed(GLFW_KEY_UP)) {
    m_position += forward * m_moveSpeed * deltaTime;
  }

  if (m_input->isKeyPressed(GLFW_KEY_DOWN)) {
    m_position -= forward * m_moveSpeed * deltaTime;
  }

  if (m_input->isKeyPressed(GLFW_KEY_LEFT)) {
    m_rotation.y += m_rotationSpeed * deltaTime;
  }

  if (m_input->isKeyPressed(GLFW_KEY_RIGHT)) {
    m_rotation.y -= m_rotationSpeed * deltaTime;
  }

  if (m_input->isKeyPressed(GLFW_KEY_SPACE) && m_isGrounded) {
    m_velocity.y = m_jumpStrength;
    m_isGrounded = false;
  }
}

void Player::applyPhysics(float deltaTime)
{
  if (!m_isGrounded) {
    m_velocity.y += m_gravity * deltaTime;
  }

  m_position += m_velocity * deltaTime;
}

void Player::checkGround()
{
  if (m_position.y <= 0.0f) {
    m_position.y = 0.0f;
    m_velocity.y = 0.0f;
    m_isGrounded = true;
  } else {
    m_isGrounded = false;
  }
}
