#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "core/Renderer.h"
#include "core/Window.h"

class Game {
  Window *window;
  Renderer *renderer;

  void update(float deltaTime);
  void render();
public:
  Game();

  bool init();
  void run();
  void shutdown();
};

#endif // !GAME_CLASS_H
