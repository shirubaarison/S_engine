#include "utils/debug.h"
#include "input/Input.h"

Input::Input() {}

bool Input::init(Window &i_window) {
  Input::window = i_window.getWindow();

  if (window == nullptr) { 
    std::cerr << "[Input] failed to initialized. Window is null.\n";
    return false;
  }

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  lastX = (double)(width/2.0f);
  lastY = (double)(height/2.0f);

#ifdef DEBUG_MESSAGES 
  std::cout << "[Input] initialized successfully.\n";
#endif

  return true;
}

bool Input::isKeyPressed(int key) {
  if (window == nullptr) return false;

  return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::isKeyReleased(int key) {
  if (window == nullptr) return false;

  return glfwGetKey(window, key) == GLFW_RELEASE;
}

bool Input::isMouseButtonPressed(int button) {
  if (window == nullptr) return false;
  
  return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

void Input::getMousePosition(double &x, double &y) const {
  if (window == nullptr) {
    x = y = -1;
    return;
  }

  glfwGetCursorPos(window, &x, &y);
}

