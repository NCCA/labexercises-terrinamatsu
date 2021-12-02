#include <iostream>
#include <chrono>
#include "Emitter.h"

int main()
{
  std::cout<<"Particle System\n";

  Emitter e(2500, {0, 20, 0});

  for(int i = 0; i < 1000; ++i)
  {
    e.update();
    //std::cout<<"**********\n";
    //e.render();
    e.saveFrame(i);
  }

  return EXIT_SUCCESS;
}