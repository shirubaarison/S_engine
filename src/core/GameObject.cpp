#include "core/GameObject.h"

namespace {
  static glm::mat4 getTransformationMatrix(const GameObject& obj) {

    glm::mat4 model = glm::mat4{1.0f};
    model = glm::translate(model, obj.getPosition());

    glm::vec3 rotation = obj.getRotation();
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, obj.getScale());

    return model;
  }
}

GameObject::GameObject(std::shared_ptr<Model> model, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
  : m_position(pos),
    m_rotation(rot),
    m_scale(scale),
    m_model(model) {}

void GameObject::render(Shader& shader, Camera& camera)
{
  if (!m_model)
    return;

  glm::mat4 view = camera.getViewMatrix();
  glm::mat4 projection = camera.getProjectionMatrix();

  glm::mat4 modelMatrix = getTransformationMatrix(*this);

  shader.setMatrix4("view", view);
  shader.setMatrix4("projection", projection);
  shader.setMatrix4("model", modelMatrix);

  m_model->draw(shader);
}
