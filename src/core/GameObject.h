#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "graphics/Camera.h"
#include "graphics/Model.h"
#include "graphics/Shader.h"
#include <glm/vec3.hpp>
#include <memory>

class GameObject {
public:
  GameObject() = default;
  GameObject(std::shared_ptr<Model> model,
             glm::vec3 pos = {0, 0, 0},
             glm::vec3 rot = {0, 0, 0},
             glm::vec3 scale = { 1, 1, 1});

  virtual ~GameObject() = default;
  virtual void update(float deltaTime) { (void)deltaTime; } // supressing unused variable warning xD
  void render(Shader& shader, Camera& camera);

  const glm::vec3& getPosition() const { return m_position; }
  const glm::vec3& getRotation() const { return m_rotation; }
  const glm::vec3& getScale() const { return m_scale; }

  void setPosition(const glm::vec3& pos) { m_position = pos; }
  void setRotation(const glm::vec3& rot) { m_rotation = rot; }
  void setScale(const glm::vec3& scale) { m_scale = scale; }
  void setModel(std::shared_ptr<Model> model) { m_model = model; }

protected:
  glm::vec3 m_position{0, 0, 0};
  glm::vec3 m_rotation{0, 0, 0};
  glm::vec3 m_scale{1, 1, 1};
  std::shared_ptr<Model> m_model;
};

#endif // !GAME_OBJECT_H
