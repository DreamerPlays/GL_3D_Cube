#include <iostream>
#include <math.h>

class fps {

private:
  double firstTime;
  int frameCount;
  double lastTime;
    
public:
  double dt;
  double passedT;
  void resetTimer();
  void frame();
  fps();
  ~fps();
};