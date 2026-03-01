#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "core/GameObject.h"
#include "input/Input.h"
#include <memory>

enum class Direction { None, Up, Down, Left, Right };

class Player : public GameObject {
public:
  Player(Input *input, std::shared_ptr<Model> model, glm::vec3 startPos = glm::vec3(0, 0, 0));

  void update(float deltaTime) override;

  glm::vec3 getVelocity() const { return m_velocity; }
  bool isGrounded() const { return m_isGrounded; }

  void setMoveSpeed(float speed) { m_moveSpeed = speed; }
  void setJumpStrength(float strength) { m_jumpStrength = strength; }

private:
  Input *m_input;

  glm::vec3 m_velocity{0, 0, 0};
  float m_gravity{-20.0f};
  float m_moveSpeed{5.0f};
  float m_rotationSpeed{3.0f};
  float m_jumpStrength{8.0f};

  bool m_isGrounded{false};

  void handleInput(float deltaTime);
  void applyPhysics(float deltaTime);
  void checkGround();
};

#endif // !PLAYER_CLASS_H
