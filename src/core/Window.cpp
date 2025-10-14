#include <iostream>

#include "core/Window.h"
#include "GLFW/glfw3.h"
#include "utils/common.h"
#include "utils/debug.h"
#include "utils/errorReporting.h"

Window::Window() : width(WIDTH), height(HEIGHT) {}

Window::Window(const std::string& title, int width, int height) 
  : width(width), height(height), mWindowTitle(title), mIsFullscreen(false) {}

Window::~Window() {
  destroy();
}

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

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "GLAD initialization failed.\n";
    return false;
  }

  configWindow(mWindow);

#ifdef DEBUG_MESSAGES
  std::cout << "[Window] GLFW Window succesfully created.\n";
#endif
  enableReportGlErrors();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, WIDTH, HEIGHT);

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


void Window::toggleFullScreen() {
  if (mWindow == nullptr) return;

  mIsFullscreen = !mIsFullscreen;
  GLFWmonitor* monitor = glfwGetWindowMonitor(mWindow);
  const GLFWvidmode* mode = glfwGetVideoMode(monitor); 

  if(mIsFullscreen) {
    glfwSetWindowMonitor(mWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
  } else {
    glfwSetWindowMonitor(mWindow, monitor,
                         (mode->width / 2) - WIDTH / 2,
                         (mode->height / 2) - HEIGHT / 2,
                         WIDTH, HEIGHT, mode->refreshRate);
  }
}

bool Window::shouldClose() {
  return mWindow ? glfwWindowShouldClose(mWindow) : false;
}

void Window::destroy() {
  if (mWindow == nullptr) 
    return;

  glfwDestroyWindow(mWindow);
}

GLFWwindow *Window::getWindow() const { return mWindow; }

int Window::getWidth() const { return width; }

int Window::getHeight() const { return height; }
