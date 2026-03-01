#include <exception>
#include <iostream>
#include <memory>
#include "resources/ResouceManager.h"
#include "core/Engine.h"
#include "core/Renderer.h"
#include "utils/debug.h"
#include "utils/common.h"

Engine::Engine() {}
Engine::~Engine() { shutdown(); }

bool Engine::init()
{
  m_window = std::make_unique<Window>(WINDOW_TITLE, WIDTH, HEIGHT);
  if (!m_window->init())
    return false;

  m_renderer = std::make_unique<Renderer>(m_window->getWidth(), m_window->getHeight());
  if (!m_renderer->init())
    return false;

  m_input = std::make_unique<Input>();
  if (!m_input->init(m_window->getWindow()))
    return false;

  m_camera = std::make_unique<Camera>(glm::vec3{-3.0f, 3.0f, 3.0f},
                                      glm::vec3{0.0f, 1.0f, 0.0f},
                                      glm::vec3{0.0f, 0.0f, 0.0f},
                                      -90.0f,
                                      20.0f);
  m_camera->setAspectRatio((float)m_window->getWidth() / m_window->getHeight());
  m_window->setCamera(m_camera.get());

  loadAssets();

#ifdef DEBUG_MESSAGES
  std::cout << "[Engine] initialization completed successfully!" << std::endl;
#endif

  return true;
}

void Engine::shutdown() {
  // TODO
}

void Engine::update(float deltaTime)
{
  if (m_input->isKeyPressed(GLFW_KEY_F)) {
    m_window->toggleFullScreen();
  }

  for (auto& obj : m_gameObjects) {
    obj->update(deltaTime);
  }

  if (m_player) {
    m_camera->setTarget(m_player->getPosition());
    m_camera->updateThirdPerson();
  }
}

void Engine::render()
{
  if (m_gameObjects.empty())
    return;

  Shader& shader = ResourceManager::getShader("default");
  shader.use();

  shader.setVector3f("lightPos", glm::vec3(10.0f, 20.0f, 10.0f));
  shader.setVector4f("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  shader.setVector3f("camPos", m_camera->getPosition());

  for (auto& obj : m_gameObjects) {
    obj->render(shader, *m_camera);
  }
}

void Engine::handleInput(double deltaTime)
{
  if (m_input->isKeyPressed(GLFW_KEY_W))
    m_camera->processKeyboard(Camera::Camera_Movement::FORWARD, deltaTime);
  if (m_input->isKeyPressed(GLFW_KEY_S))
    m_camera->processKeyboard(Camera::Camera_Movement::BACKWARD, deltaTime);
  if (m_input->isKeyPressed(GLFW_KEY_A))
    m_camera->processKeyboard(Camera::Camera_Movement::LEFT, deltaTime);
  if (m_input->isKeyPressed(GLFW_KEY_D))
    m_camera->processKeyboard(Camera::Camera_Movement::RIGHT, deltaTime);

  if (m_input->isKeyPressed(GLFW_KEY_ESCAPE)) {
    m_input->setMouseCaptured(!m_input->getMouseCaptured());
    m_camera->setThirdPersonMode(!m_camera->isThirdPerson());
  }

  if (m_input->getMouseCaptured()) {
    double xoffset, yoffset;
    m_input->getMouseOffset(xoffset, yoffset);
    m_camera->processMouseMovement(xoffset, yoffset);
  }
}

void Engine::run()
{
  float deltaTime = 0.0f;
  float mLastFrame = 0.0f;

  while (!m_window->shouldClose()) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    m_renderer->render();

    handleInput(deltaTime);
    update(deltaTime);
    render();

    m_window->update();
  }
}

void Engine::loadAssets()
{
  ResourceManager::loadShader("default", "shaders/default.vert", "shaders/default.frag");

  try {
    auto playerModel = std::make_shared<Model>("assets/models/churrasqueira/commercial_prop_for_brazilian_street_food_-_68.obj");

    auto player = std::make_unique<Player>(m_input.get(),
                                           playerModel,
                                           glm::vec3(0.0f, 0.5f, 0.0f)
                                           );
    m_player = player.get();
    m_gameObjects.push_back(std::move(player));

    std::cout << "[Engine] Player created" << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

#ifdef DEBUG_MESSAGES
  std::cout << "[Engine] assets loaded" << std::endl;
#endif
}
