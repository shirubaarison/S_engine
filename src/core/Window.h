#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include "graphics/Camera.h"
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
  Window(const std::string& title, int width, int height);
  ~Window();

  bool init();
  void shutdown();
  void update();
  bool shouldClose();

  void toggleFullScreen();

  GLFWwindow *getWindow() const { return m_window; }
  int getWidth() const { return m_width;}
  int getHeight() const { return m_height; }
  Camera *getCamera() const { return m_camera; }

  void setCamera(Camera* camera) { m_camera = camera; }
private:
  int m_width;
  int m_height;
  std::string m_windowTitle;
  GLFWwindow *m_window;

  bool m_isFullscreen;

  Camera* m_camera = nullptr;
};

#endif // !WINDOW_CLASS_H
