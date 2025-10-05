#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include "core/Window.h"

class Input {
  GLFWwindow *window;
  double lastX;
  double lastY;
public:
  Input();

  bool init(Window &iWindow);
  bool isKeyPressed(int key);
  bool isKeyReleased(int key);

  bool isMouseButtonPressed(int button);

  void getMousePosition(double &x, double &y) const;
  void setCurosrPosition(double x, double y);
};

#endif // !INPUT_CLASS_H
