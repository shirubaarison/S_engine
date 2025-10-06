#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
  int width;
  int height;
  GLFWwindow *mWindow;
public:
  Window();
  bool init();
  void shutdown();
  void update();
  bool shouldClose();

  GLFWwindow *getWindow() const;

  int getWidth() const;
  int getHeight() const;
};

#endif // !WINDOW_CLASS_H
