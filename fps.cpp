#include "fps.h"

fps::fps(double start) {
  fps::firstTime = start;
  fps::frameCount = 0;
}

int fps::getFPS(double currentTime) {
  double dt = currentTime - fps::firstTime;
  fps::firstTime = currentTime;
  double fps = (fps::frameCount/dt);
  fps::frameCount = 0;
  return round(fps);
}

void fps::countFrame() {
  fps::frameCount = fps::frameCount + 1;
}

double fps::getCurrentDT(double currentTime) {
  double dt = currentTime - fps::firstTime;
  return dt;
}

fps::~fps() {
}