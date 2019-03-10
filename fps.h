#include <iostream>
#include <math.h>
#include <chrono>

class fps {

private:
  std::chrono::_V2::high_resolution_clock::time_point stopT;
  std::chrono::_V2::high_resolution_clock::time_point startT;
  std::chrono::high_resolution_clock timer;
    
public:
  double dt;
  void calcDt();
  fps();
  void start();
  void stop();
  ~fps();
};