#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
  GLFWwindow *mWindow;
public:
  Window();
  bool init();
  void shutdown();
  void update();
  bool shouldClose();

  GLFWwindow *getWindow() const;
};

#endif // !WINDOW_CLASS_H
