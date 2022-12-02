#include "population.h"
#include <iostream>
#include "string.h"
#include "string"
#include <cstdio>

using namespace std;

int main() {
  population mypopulation;
  mypopulation.generate_population(6, 4);
  mypopulation.set_mutation(0.7);
  mypopulation.print_population();
  
  Pixel* target;
  target = new Pixel[4];
  target[0] = {15, 167, 244};
  target[1] = {45, 143, 23};
  target[2] = {156, 181, 22};
  target[3] = {10, 246, 147};
  
  mypopulation.set_target(target, 4);
  mypopulation.print_target();
  
  mypopulation.select_parents();
  mypopulation.print_parents();
  mypopulation.set_nCrossover(2);
  mypopulation.generate_new_population(0);
  mypopulation.print_population();
  return 0;
}
