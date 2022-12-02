#include "population.h"
#include <iostream>
#include <string>

using namespace std;

population::population() {
	individuals = NULL;
	nIndividuals = 0;
  parent1Index = -1;
  parent2Index = -1;
  parent1 = NULL;
  parent2 = NULL;
}

population::~population() {
  if (this->individuals == NULL) {
    return;
  }
		this->individuals = NULL;
		this->nIndividuals = 0;
}

void population::generate_population(int popSize, int nGenes) {
	this->individuals = new genome[popSize];
	this->nIndividuals = popSize;
  this->nGenes = nGenes;
	for (int i = 0; i < popSize; i++) {
    this->individuals[i].allocate(nGenes);
		this->individuals[i].randomize();
	}
}

void population::set_target(Pixel* target, int imageSize) {
  this->targetGenome.allocate(imageSize);
	for (int i = 0; i < imageSize; i++) {
		this->targetGenome.setPixel(i, target[i]);
	}
}

void population::select_parents() {
	double parent1Fitness = 100.0;
	double parent2Fitness = 100.0;
	for (int i = 0; i < nIndividuals; i++) {
		double error = this->individuals[i].calculate_overall_fitness(this->targetGenome); 
    cout << "Overall fitness of individual " << i << ": " << error << endl;
		if (error < parent1Fitness) {
			parent2Fitness = parent1Fitness;
			this->parent2Index = this->parent1Index;
			parent1Fitness = error;
			parent1Index = i;
    }
   
   if (this->parent1Index != -1) {
     this->parent1 = new Pixel[nGenes];
     this->parent2 = new Pixel[nGenes];
     for (int i; i < nGenes; i++) {
       parent1[i].red = this->individuals[parent1Index].getRed(i);
       parent1[i].green = this->individuals[parent1Index].getGreen(i);
       parent1[i].blue = this->individuals[parent1Index].getBlue(i);
       
       parent2[i].red = this->individuals[parent2Index].getRed(i);
       parent2[i].green = this->individuals[parent2Index].getGreen(i);
       parent2[i].blue = this->individuals[parent2Index].getBlue(i);       
     }
   }		
	}
}

void population::set_nCrossover(int nCrossover = 1) {
  if (0 <= this->nCrossover && this->nCrossover < this->nGenes) {
	  this->nCrossover = nCrossover;
  }
}

int population::get_nCrossover() {
	return this->nCrossover;
}

void population::set_mutation(double mRate) {
	for (int i = 0; i < nIndividuals; i++) {
		this->individuals[i].set_mRate(mRate);
	}
}

void population::generate_new_population(int useRoulette=0) {
  if (useRoulette == 1) {
    return;
  }
  for (int i = 0; i < this->nIndividuals; i=i+2) {
    for (int j = 0; j < this->nGenes; j++) {
      /*print_parents();
      cout << individuals[i].getRed(j) << " " << individuals[i].getGreen(j) << " " << individuals[i].getBlue(j) << endl;
      cout << parent1[j].red << " " << parent1[j].green << " " << parent1[j].blue << " " << endl;
      cout << individuals[i+1].getRed(j) << " " << individuals[i+1].getGreen(j) << " " << individuals[i+1].getBlue(j) << endl;
      cout << parent2[j].red << " " << parent2[j].green << " " << parent2[j].blue << " " << endl;*/
      if (j < this->nCrossover) {
        this->individuals[i].setPixel(j, this->parent1[j]);
        this->individuals[i+1].setPixel(j, this->parent2[j]);
      }
      else {
        this->individuals[i].setPixel(j, this->parent2[j]);
        this->individuals[i+1].setPixel(j, this->parent1[j]);
      }
      
      
      // mutate after crossover
      //individuals[i].mutate();
      //individuals[i+1].mutate();
    }
  }
}

double population::calculate_overall_fitness() {
	double sumFitness;
	for (int i = 0; i < this->nIndividuals; i++) {
		sumFitness += this->individuals[i].calculate_overall_fitness(targetGenome); 
	}
  double res = sumFitness / this->nIndividuals;
	return res;
}

void population::print_parents() {
	if (this->parent1Index == -1) {
		cout << "Parents not found" << endl;
	}
	else {
		cout << "Parent 1: ";
		this->individuals[parent1Index].print();
    cout << endl;
		cout << "Parent 2: ";
		this->individuals[parent2Index].print();
    cout << endl;
	}
}

void population::print_target() {
  cout << "TargetGenome: ";
  this->targetGenome.print();
  cout << endl;
}

void population::print_population() {
	cout << "Number of crossover points: " << this->nCrossover << endl;
	cout << "Mutation rate: " << this->individuals[0].get_mRate() << endl;
	for (int i = 0; i < nIndividuals; i++) {
		cout << "Individual " << i << ": ";
		individuals[i].print();
    cout << endl;
	}
}