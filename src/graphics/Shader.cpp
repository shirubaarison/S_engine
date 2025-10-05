#include "graphics/Shader.h"
#include "utils/debug.h"

#include <fstream>

#define LOG_SIZE 1024

std::string get_file_contents(const char *path) {
  std::string result = "";
  std::ifstream file(path);

  if (!file) {
    std::cerr << "Error trying to open file: '" << path << "'.\n";
    return result;
  }

  std::string line = "";
  if (file.is_open()) {
    while (std::getline(file, line)) {
      result += line + '\n';
    }
    file.close();
  }

  return result;
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

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  std::string vertexContents = get_file_contents(vertexPath);
  std::string fragmentContents = get_file_contents(fragmentPath);

  const char *vertexSource = vertexContents.c_str();
  const char *fragmentSource = fragmentContents .c_str();

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

#ifdef DEBUG_MESSAGES 
  std::cout << "[Shader] shaders: '" << vertexPath << "' and '" << fragmentPath << "' loaded successfully." << std::endl;
#endif
}

Shader::Shader() {}

Shader &Shader::use() {
  glUseProgram(this->ID);
  return *this;
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
