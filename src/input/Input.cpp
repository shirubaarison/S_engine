#include "GLFW/glfw3.h"
#include "utils/debug.h"
#include "input/Input.h"

Input::Input() {}

bool Input::init(GLFWwindow* window) {
  m_window = window;

  if (m_window == nullptr) {
    std::cerr << "[Input] failed to initialized. m_window is null.\n";
    return false;
  }

  int width, height;
  glfwGetWindowSize(m_window, &width, &height);

  lastX = (double)(width/2.0f);
  lastY = (double)(height/2.0f);

#ifdef DEBUG_MESSAGES
  std::cout << "[Input] initialized successfully.\n";
#endif

  return true;
}

bool Input::isKeyPressed(int key) {
  if (m_window == nullptr) return false;

  return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool Input::isKeyReleased(int key) {
  if (m_window == nullptr) return false;

  return glfwGetKey(m_window, key) == GLFW_RELEASE;
}

bool Input::isMouseButtonPressed(int button) {
  if (m_window == nullptr) return false;
  
  return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}

void Input::getMousePosition(double &x, double &y) const {
  if (m_window == nullptr) {
    x = y = -1;
    return;
  }

  glfwGetCursorPos(m_window, &x, &y);
}

