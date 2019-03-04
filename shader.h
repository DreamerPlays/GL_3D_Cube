#pragma once
#define SH_FILEPATH true
#define SH_SOURCE false
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

class shader {
  private:
    unsigned int program;
    std::vector<unsigned int> shaders;
    std::string parseShader(const std::string&);
    int lastUniformID;
    char* lastUniformName;

  public:
    shader();
    ~shader();
    void bind();
    void unbind();
    void addShader(unsigned int, const std::string&, bool);
    void compileShader();
    void setUniform4f(const char*, float, float, float, float);
    void setUniform3f(const char*, float, float, float);
    void setUniformMat4fv(const char*, glm::mat4);
};