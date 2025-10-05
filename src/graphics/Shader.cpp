#include "graphics/Shader.h"

#define LOG_SIZE 1024

Shader &Shader::use() {
  glUseProgram(this->ID);
  return *this;
}

static void checkCompilerError(GLuint object, std::string type) {
  int success;
  char infoLog[LOG_SIZE];

  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, LOG_SIZE, NULL, infoLog);
      std::cerr << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
        << infoLog << "\n -- ----------------------------------------------- --\n";

      return;
    }
  }

  glGetProgramiv(object, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(object, LOG_SIZE, NULL, infoLog);
    std::cerr << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
      << infoLog << "\n -- ----------------------------------------------- --\n";
  }
}

void Shader::compile(const char *vertexSource, const char *fragmentSource) {
  GLuint sVertex, sFragment;

  // Vertex 
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, NULL);
  glCompileShader(sVertex);

  checkCompilerError(sVertex, "VERTEX");

  // Fragment 
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, NULL);
  glCompileShader(sFragment);

  checkCompilerError(sFragment, "FRAGMENT");

  // Shader program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, sVertex);
  glAttachShader(this->ID, sFragment);
  glLinkProgram(this->ID);

  checkCompilerError(this->ID, "PROGRAM");

  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
}

void Shader::setFloat    (const char *name, float value) const {
  glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::setInteger  (const char *name, int value) const {
  glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVector2f (const char *name, float x, float y) const {
  glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::setVector2f (const char *name, const glm::vec2 &value) const {
  glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::setVector3f (const char *name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::setVector3f (const char *name, const glm::vec3 &value) const {
  glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
