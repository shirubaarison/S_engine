#include "graphics/Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
  : m_position{position},
    m_worldUp{up},
    m_yaw{yaw},
    m_pitch{pitch},
    m_moveSpeed{DEFAULT_SPEED},
    m_mouseSen{DEFAULT_SENSITIVITY},
    m_zoom{DEFAULT_ZOOM},
    m_nearPlane{DEFAULT_NEAR_PLANE},
    m_farPlane{DEFAULT_FAR_PLANE} 
{
  updateCameraVectors();
}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() const
{
  return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
  return glm::perspective(glm::radians(m_zoom), m_aspectRatio, m_nearPlane,
                          m_farPlane);
}

void Camera::setPosition(const glm::vec3 &pos)
{
  m_position = pos;
  updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
  float velocity = m_moveSpeed * deltaTime;

  if (direction == Camera_Movement::FORWARD)
    m_position += m_front * velocity;
  if (direction == Camera_Movement::BACKWARD)
    m_position -= m_front * velocity;
  if (direction == Camera_Movement::LEFT)
    m_position -= m_right * velocity;
  if (direction == Camera_Movement::RIGHT)
    m_position += m_right * velocity;
  if (direction == Camera_Movement::UP)
    m_position += m_up * velocity;
  if (direction == Camera_Movement::DOWN)
    m_position -= m_up * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset,
                                  bool constrainPitch)
{
  xoffset *= m_mouseSen;
  yoffset *= m_mouseSen;

  m_yaw += xoffset;
  m_pitch += yoffset;

  if (constrainPitch) {
    if (m_pitch > 89.0f)
      m_pitch = 89.0f;
    if (m_pitch < -89.0f)
      m_pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::updateCameraVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);

  m_right = glm::normalize(glm::cross(m_front, m_worldUp));
  m_up = glm::normalize(glm::cross(m_right, m_front));
}
