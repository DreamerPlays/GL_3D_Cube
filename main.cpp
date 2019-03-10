#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include "fps.h"
#include <thread>

#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "shader.h"
#include "vertexArray.h"
#include "Robject.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main(int argc, char** argv)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;


  /* Create a windowed to know whats the highest opengl version supported*/
  GLFWwindow* context = glfwCreateWindow(1, 1, "contextgetter", NULL, NULL);
  if (!context)
  {
    glfwTerminate();
    return -1;
  }
  glfwSetWindowPos(context, 0, 0);

  /* Make the window's context current */
  glfwMakeContextCurrent(context);

  std::string version((char*)glGetString(GL_VERSION));
  std::cout << "highest context: " << version.at(0) << "." << version.at(2) << std::endl;

  glfwDestroyWindow(context);

  const int maj = (const int)version.at(0) - 48;
  const int min = (const int)version.at(2) - 48;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  // 4xMSAA
  glfwWindowHint(GLFW_SAMPLES, 4);


  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(800, 800, "GL_3D_Cube", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    std::cout << "Error initialilzing GLEW!" << std::endl;


  std::cout << glGetString(GL_VERSION) << std::endl;

  float positions[] = {
    -1.0f, -1.0f, -1.0f, //0
     1.0f, -1.0f, -1.0f, //1
     1.0f,  1.0f, -1.0f, //2
    -1.0f,  1.0f, -1.0f, //3
    -1.0f, -1.0f,  1.0f, //4
     1.0f, -1.0f,  1.0f, //5
     1.0f,  1.0f,  1.0f, //6
    -1.0f,  1.0f,  1.0f  //7
  };

  unsigned int indecies[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    3, 7
  };

  vertexBufferLayout* layout = new vertexBufferLayout;
  layout->push<float>(3);
  Robject* cube = new Robject(positions, 3 * 8, indecies, 2 * 12, layout);
  
  shader* standard = new shader();
  standard->addShader(GL_VERTEX_SHADER, "./shaders/vertex.shader", SH_FILEPATH);
  standard->addShader(GL_FRAGMENT_SHADER, "./shaders/fragment.shader", SH_FILEPATH);
  standard->compileShader();
  standard->bind();
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
  glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0,0,-5),glm::vec3(0,0,0),glm::vec3(0,1,0));
  glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 1.0f / 1.0f, 0.1f, 100.0f);
  glm::mat4 M3D = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scalingMatrix;
  standard->setUniformMat4fv("m_3d", M3D);

  float angle = 0;
  float alpha = 1.0f;

  glBindVertexArray(0);
  glUseProgram(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  fps* tfps = new fps();
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    standard->bind();
    standard->setUniform3f("u_Color", (1.0f+(float)sin(alpha))/2.0f, 1.0f, 1.0f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 M3D = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scalingMatrix;
    standard->setUniformMat4fv("m_3d", M3D);
    standard->bind();

    glLineWidth(2.0f);
    cube->draw(GL_LINES, 12 * 2, 0);

    alpha += 0.5 * tfps->dt;
    angle += 45.0 * tfps->dt;

    glfwSwapBuffers(window);
    glfwPollEvents();
    tfps->stop();
    tfps->calcDt();
    tfps->start();
  }

  delete cube;
  delete standard;
  delete tfps;

  glfwTerminate();
  return 0;
}
