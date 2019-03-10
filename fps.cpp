#include "fps.h"
#include "GLFW/glfw3.h"
#include <chrono>

fps::fps() {
  fps::start();
}

fps::~fps() {
}

void fps::calcDt() {
  using ms = std::chrono::duration<long double, std::ratio<1LL,1LL>>;
  fps::dt = std::chrono::duration_cast<ms>(fps::stopT - fps::startT).count();
}

void fps::start() {
  fps::startT = fps::timer.now();
}

void fps::stop() {
  fps::stopT = fps::timer.now();
}