#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "glm/ext/vector_float2.hpp"
#include "input/Input.h"
class Player {
  Input *input;
  float baseSpeed;

  glm::vec2 pos;
  glm::vec2 velocity;

  int width, height;

  void handleKeyboardInput(float deltaTime);
public:
  Player(Input *input, glm::vec2 startPos = glm::vec2(0, 0));

  void update(float deltaTime);

  glm::vec2 getPos() const;
  glm::vec2 getVelocity() const;
  int getWidth() const;
  int getHeight() const;

  void setPos(glm::vec2 pos);
};

#endif // !PLAYER_CLASS_H
