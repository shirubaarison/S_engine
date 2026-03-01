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
  void getMouseOffset(double &xoffset, double &yoffset);
  void setCurosrPosition(double x, double y);

  void setMouseCaptured(bool captured);

  bool getMouseCaptured() const { return m_mouseCaptured; }
private:
  GLFWwindow *m_window;

  double lastX;
  double lastY;
  bool firstMouse{true};
  bool m_mouseCaptured{false};
};

#endif // !INPUT_CLASS_H
