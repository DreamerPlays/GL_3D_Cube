#define SH_FILEPATH true
#define SH_SOURCE false
#define GLEW_STATIC
#include "shader.h"
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <malloc.h>
#include <string.h>
#include "renderer.h"
#include <glm/gtc/type_ptr.hpp>

shader::shader() {

}

void shader::compileShader() {
  GLCall(shader::program = glCreateProgram());
  for (unsigned int id : shader::shaders) {
    GLCall(glAttachShader(shader::program, id));
  }
  GLCall(glLinkProgram(shader::program));
  GLCall(glValidateProgram(shader::program));

  std::vector<unsigned int>().swap(shader::shaders);
}

shader::~shader() {
  GLCall(glDeleteProgram(shader::program));
}

void shader::bind() {
  GLCall(glUseProgram(shader::program));
}

void shader::unbind() {
  GLCall(glUseProgram(0));
}

void shader::addShader(unsigned int type, const std::string& source, bool ftype) {
  if (ftype) {
    shader::addShader(type, shader::parseShader(source), SH_SOURCE);
  }else {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int length;
      GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
      char* message = (char*)_malloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(id, length, &length, message));
      std::cout << "Failed to compile " << type << "shader!" << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(id));
      return;
    }
    shaders.push_back(id);
  }
}

std::string shader::parseShader(const std::string& filepath) {
  std::ifstream stream(filepath);
  if(stream.fail()){
    std::cout << "Shaderfile not found!: '" << filepath << "'" << std::endl;
  }
  std::stringstream ss;
  std::string line;
  while (std::getline(stream, line)) {
    ss << line << "\n";
  }

  return ss.str();
}

void shader::setUniform4f(const char* loc, float v0, float v1, float v2, float v3) {
  int id;
  glGetIntegerv(GL_CURRENT_PROGRAM,&id);

  if (id != shader::program) {
    std::cout << "Shader not bound! Cannot apply Uniform" << std::endl;
    return;
  }
  if (shader::lastUniformName != loc) {
    GLCall(shader::lastUniformID = glGetUniformLocation(shader::program, loc));
    ASSERT(shader::lastUniformID != -1);
    shader::lastUniformName = (char*)loc;
  }
  GLCall(glUniform4f(shader::lastUniformID, v0, v1, v2, v3))
}

void shader::setUniform3f(const char* loc, float v0, float v1, float v2) {
  int id;
  glGetIntegerv(GL_CURRENT_PROGRAM,&id);

  if (id != shader::program) {
    std::cout << "Shader not bound! Cannot apply Uniform" << std::endl;
    return;
  }
  if (shader::lastUniformName != loc) {
    GLCall(shader::lastUniformID = glGetUniformLocation(shader::program, loc));
    ASSERT(shader::lastUniformID != -1);
    shader::lastUniformName = (char*)loc;
  }
  GLCall(glUniform3f(shader::lastUniformID, v0, v1, v2));
}

void shader::setUniformMat4fv(const char* loc, glm::mat4 v0) {
  int id;
  glGetIntegerv(GL_CURRENT_PROGRAM,&id);

  if (id != shader::program) {
    std::cout << "Shader not bound! Cannot apply Uniform" << std::endl;
    return;
  }
  if (shader::lastUniformName != loc) {
    GLCall(shader::lastUniformID = glGetUniformLocation(shader::program, loc));
    ASSERT(shader::lastUniformID != -1);
    shader::lastUniformName = (char*)loc;
  }
  GLCall(glUniformMatrix4fv(shader::lastUniformID, 1, GL_FALSE, glm::value_ptr(v0)));
}