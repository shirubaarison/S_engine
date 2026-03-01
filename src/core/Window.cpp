#include <iostream>
#include <glad/glad.h>
#include "core/Window.h"
#include "GLFW/glfw3.h"
#include "graphics/Camera.h"
#include "utils/common.h"
#include "utils/debug.h"

namespace
{
  static void setHints()
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }

  static void windowSizeCallback(GLFWwindow *window, int width, int height)
  {
    glViewport(0, 0, width, height);

    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (win && win->getCamera()) {
    float aspectRatio = (float)width / (float)height;
    win->getCamera()->setAspectRatio(aspectRatio);
  }
  }

  static void configWindow(GLFWwindow *window, Window *windowInstance)
  {
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (mode->width / 2) - (WIDTH / 2),
                    (mode->height / 2) - (HEIGHT / 2));

    glfwSetWindowUserPointer(window, windowInstance);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwFocusWindow(window);
  }

  static void glfwErrorCallback(int code, const char* desc) { std::cerr << "GLFW Error: (" << code << "): " << desc << "\n"; }
}

Window::Window(const std::string& title, int width, int height)
  : m_width(width),
    m_height(height),
    m_windowTitle(title),
    m_window(nullptr),
    m_isFullscreen(false),
    m_camera(nullptr) {}

Window::~Window()
{
  if (m_window == nullptr)
    return;

  glfwDestroyWindow(m_window);
}

bool Window::init()
{
  glfwSetErrorCallback(glfwErrorCallback);

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW.\n";
    return false;
  }

  setHints();

  m_window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, nullptr, nullptr);
  if (m_window == nullptr) {
    std::cerr << "Failed to create GLFW window.\n";
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(m_window);

  configWindow(m_window, this);

#ifdef DEBUG_MESSAGES
  std::cout << "[Window] GLFW Window succesfully created.\n";
#endif

  return true;
}

void Window::shutdown()
{
  if (m_window == nullptr)
    return;

  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void Window::update()
{
  if (m_window == nullptr)
    return;

  glfwPollEvents();
  glfwSwapBuffers(m_window);
}


void Window::toggleFullScreen()
{
  if (m_window == nullptr) return;

  m_isFullscreen = !m_isFullscreen;
  GLFWmonitor* monitor = glfwGetWindowMonitor(m_window);
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  if(m_isFullscreen) {
    glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
  } else {
    glfwSetWindowMonitor(m_window, monitor,
                         (mode->width / 2) - WIDTH / 2,
                         (mode->height / 2) - HEIGHT / 2,
                         WIDTH, HEIGHT, mode->refreshRate);
  }
}

bool Window::shouldClose() { return m_window ? glfwWindowShouldClose(m_window) : false; }
