#include "genome.h"

#include <iostream>
#include "string.h"
#include "string"
#include <cstdio>

using namespace std;

int main() {
  genome myGenome;
  
  myGenome.print();
  cout << endl;
  
  cout << "Allocating 4 genes to the object" << endl;
  myGenome.allocate(4);
  myGenome.print();
  cout << endl;
  
  cout << "Randomizing the RGB of all genes in the object" << endl;
  myGenome.randomize();
  myGenome.print();
  cout << endl;
  
  cout << "Setting Blue at index 0 to 226" << endl;
  myGenome.setBlue(0, 226);
  myGenome.print();
  cout << endl;
  
  cout << "Setting mRate to 0.5 and mutate all genes in the object" << endl;
  myGenome.set_mRate(0.5);
  myGenome.mutate();
  myGenome.print();
  cout << endl;
  
  cout << "Calculating gene fitness of gene at index 2 to RGB: {15, 167, 244}" << endl;
  cout << myGenome.calculate_gene_fitness(2, {15, 167, 244}) << endl;
   
  cout << "Calculating overall fitness of genes to myPixel [{15, 167, 244}, {1, 2, 3}, {4, 9, 10}, {12, 13, 14}]" << endl;
  Pixel* myPixel;
  myPixel = new Pixel[4];
  myPixel[0] = {15, 167, 244};
  myPixel[1] = {1, 2, 3};
  myPixel[2] = {4, 9, 10};
  myPixel[3] = {12, 13, 14};
  cout << myGenome.calculate_overall_fitness(myPixel, 4) << endl;
  cout << endl;
  
  cout << "Setting pixel at index 3 to {4, 9, 10}" << endl;
  myGenome.setPixel(3, {4, 9, 10});
  myGenome.print();
  cout << endl;
  
  cout << "Calling unit testing" << endl;
  myGenome.UnitTest();
  
  return 0;
}
