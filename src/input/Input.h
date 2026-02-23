#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include "GLFW/glfw3.h"

class Input {
public:
  Input();

  bool init(GLFWwindow* iWindow);
  bool isKeyPressed(int key);
  bool isKeyReleased(int key);

  bool isMouseButtonPressed(int button);

  void getMousePosition(double &x, double &y) const;
  void setCurosrPosition(double x, double y);
private:
  GLFWwindow *m_window;

  double lastX;
  double lastY;
};

#endif // !INPUT_CLASS_H
