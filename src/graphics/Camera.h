#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include <glm/glm.hpp>

class Camera {
public:
  enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
  };

  static constexpr float DEFAULT_YAW          = -90.0f;
  static constexpr float DEFAULT_PITCH        = 0.0f;
  static constexpr float DEFAULT_SPEED        = 2.5f;
  static constexpr float DEFAULT_SENSITIVITY  = 0.1f;
  static constexpr float DEFAULT_ZOOM         = 45.0f;
  
  static constexpr float DEFAULT_NEAR_PLANE   = 0.1f;
  static constexpr float DEFAULT_FAR_PLANE    = 100.0f;

  Camera(glm::vec3 position = glm::vec3{0, 0, 0},
         glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f},
         float yaw = DEFAULT_YAW,
         float pitch = DEFAULT_PITCH);
  ~Camera();

  glm::mat4 getViewMatrix() const;
  glm::mat4 getProjectionMatrix(float aspectRatio) const;

  void processKeyboard(Camera_Movement direction, float deltaTime);
  void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

  glm::vec3 getPosition() const { return m_position; }
  glm::vec3 getFront() const { return m_front; }
  glm::vec3 getUp() const { return m_up; }
  glm::vec3 getRight() const { return m_right; }
  glm::vec3 getWorldUp() const { return m_worldUp; }

  float getYaw() const { return m_yaw; }
  float getZoom() const { return m_zoom; }
  float getMoveSpeed() const { return m_moveSpeed; }
  float getMouseSen() const { return m_mouseSen; }
  float getNearPlane() const { return m_nearPlane; }
  float getFarPlane() const { return m_farPlane; }

  void setPosition(const glm::vec3& pos);
  void setMovementSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }
  void setMouseSensibility(float sensibility) { m_mouseSen = sensibility; }

private:
  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;

  glm::vec3 m_worldUp;

  float m_yaw;
  float m_pitch;

  float m_moveSpeed;
  float m_mouseSen;
  float m_zoom;

  float m_nearPlane;
  float m_farPlane;

  void updateCameraVectors();
};

#endif // !CAMERA_CLASS
