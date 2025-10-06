#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "core/SpriteRenderer.h"
#include "core/Window.h"
#include "input/Input.h"

class Game {
  Window *window;
  SpriteRenderer *renderer;
  Input *input;

  void update(float deltaTime);
  void render();
  
  void loadAssets();
public:
  Game();

  bool init();
  void run();
  void shutdown();
};

#endif // !GAME_CLASS_H
