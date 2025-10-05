#include <iostream>

#include "core/Window.h"
#include "utils/common.h"
#include "utils/debug.h"

Window::Window() {}

static void setHints() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

static void windowSizeCallback(GLFWwindow *window, int width, int height) {
  (void)window; // supress unused variable
  glViewport(0, 0, width, height);
}

static void configWindow(GLFWwindow *window) {
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(window, (mode->width / 2) - (WIDTH / 2),
                   (mode->height / 2) - (HEIGHT / 2));

  glfwSetWindowUserPointer(window, glfwGetWindowUserPointer(window));
  glfwSetWindowSizeCallback(window, windowSizeCallback);
  glfwFocusWindow(window);
}

bool Window::init() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW.\n";
    return false;
  }

  setHints();

  mWindow = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, nullptr, nullptr);
  if (mWindow == nullptr) {
    std::cerr << "Failed to create GLFW window.\n";
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(mWindow);

  configWindow(mWindow);

#ifdef DEBUG_MESSAGES
  std::cout << "[Window] GLFW Window succesfully created.\n";
#endif

  return true;
}

void Window::shutdown() {
  if (mWindow == nullptr)
    return;

  glfwDestroyWindow(mWindow);
  glfwTerminate();
}

void Window::update() {
  if (mWindow == nullptr)
    return;

  glfwPollEvents();
  glfwSwapBuffers(mWindow);
}

bool Window::shouldClose() {
  return mWindow ? glfwWindowShouldClose(mWindow) : false;
}

GLFWwindow *Window::getWindow() const { return mWindow; }
