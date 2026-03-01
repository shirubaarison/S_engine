#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include "core/GameObject.h"
#include "core/Renderer.h"
#include "core/Window.h"
#include "game/Player.h"
#include "input/Input.h"
#include "graphics/Camera.h"
#include <memory>

class Engine {
public:
  Engine();
  ~Engine();

  bool init();
  void run();
  void shutdown();

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<Renderer> m_renderer;
  std::unique_ptr<Input> m_input;
  std::unique_ptr<Camera> m_camera;
  std::vector<std::unique_ptr<GameObject>> m_gameObjects;

  Player *m_player = nullptr;

  void update(float deltaTime);
  void render();
  void handleInput(double deltaTime);
  void loadAssets();
};

#endif // !ENGINE_CLASS_H
