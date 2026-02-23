#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <GLFW/glfw3.h>
#include <string>

class Window {
  int width;
  int height;
  std::string mWindowTitle;
  GLFWwindow *mWindow;

  bool mIsFullscreen;

  void destroy();
public:
  Window();
  Window(const std::string& title, int width, int height);
  ~Window();

  bool init();
  void shutdown();
  void update();
  bool shouldClose();

  void toggleFullScreen();

  GLFWwindow *getWindow() const;

  int getWidth() const;
  int getHeight() const;
};

#endif // !WINDOW_CLASS_H
