#include <iostream>
#include <math.h>

class fps {

private:
  double firstTime;
  int frameCount;
    
public:
  fps(double);
  ~fps();
  int getFPS(double);
  void countFrame();
  double getCurrentDT(double);
};