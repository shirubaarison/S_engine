#include "graphics/Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 target, float yaw, float pitch)
  : m_position{position},
    m_target{target},
    m_worldUp{up},
    m_yaw{yaw},
    m_pitch{pitch},
    m_moveSpeed{DEFAULT_SPEED},
    m_mouseSen{DEFAULT_SENSITIVITY},
    m_zoom{DEFAULT_ZOOM},
    m_nearPlane{DEFAULT_NEAR_PLANE},
    m_farPlane{DEFAULT_FAR_PLANE},
    m_orbitDistance{8.0f},
    m_orbitHeightOffset{2.0f},
    m_thirdPersonMode{false}
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
  if (m_thirdPersonMode) {
    m_target = pos;
    updateThirdPerson();
  } else {
    m_position = pos;
    updateCameraVectors();
  }
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
    if (m_thirdPersonMode) {
      if (m_pitch > 60.0f)
        m_pitch = 60.0f;
      if (m_pitch < -30.0f)
        m_pitch = -30.0f;
    } else {
      if (m_pitch > 89.0f)
        m_pitch = 89.0f;
      if (m_pitch < -89.0f)
        m_pitch = -89.0f;
    }
  }

  if (m_thirdPersonMode) {
    updateThirdPerson();
  } else {
    updateCameraVectors();
  }
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

void Camera::updateThirdPerson()
{
  if (!m_thirdPersonMode)
    return;

  glm::vec3 lookAtPoint = m_target + glm::vec3(0, m_orbitHeightOffset, 0);

  float camX = lookAtPoint.x + m_orbitDistance * cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  float camY = lookAtPoint.y + m_orbitDistance * sin(glm::radians(m_pitch));
  float camZ = lookAtPoint.z + m_orbitDistance * sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

  m_position = glm::vec3{camX, camY, camZ};

  m_front = glm::normalize(lookAtPoint - m_position);
  m_right = glm::normalize(glm::cross(m_front, m_worldUp));
  m_up = glm::normalize(glm::cross(m_right, m_front));
}
