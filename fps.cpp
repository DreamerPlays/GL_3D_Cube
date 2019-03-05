#include "fps.h"
#include "GLFW/glfw3.h"

fps::fps() {
  fps::firstTime = glfwGetTime();
}

fps::~fps() {
}

void fps::frame() {
  double time = glfwGetTime();
  fps::dt = time - fps::lastTime;
  fps::lastTime = time;
  fps::passedT = time - fps::firstTime;
}

void fps::resetTimer() {
  fps::firstTime = glfwGetTime();
  fps::passedT = 0;
}