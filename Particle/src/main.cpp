#include <iostream>
#include <chrono>
#include "Emitter.h"

int main()
{
  std::cout<<"Particle System\n";

  Emitter e(10);
  e.render();

  return EXIT_SUCCESS;
}