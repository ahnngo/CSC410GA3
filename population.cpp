#include "population.h"
#include <iostream>
#include <string>

using namespace std;

population::population() {
  // constructor
	individuals = NULL;
	nIndividuals = 0;
  parent1Index = -1;
  parent2Index = -1;
  parent1 = NULL;
  parent2 = NULL;
  nCrossover = 1;
}

population::~population() {
  // destructor
  if (this->individuals == NULL) {
    return;
  }
		this->individuals = NULL;
		this->nIndividuals = 0;
}

void population::generate_population(int popSize, int nGenes) {
  // create a population of popSize individuals, each of which have nGenes genes
	this->individuals = new genome[popSize];
	this->nIndividuals = popSize;
  this->nGenes = nGenes;
	for (int i = 0; i < popSize; i++) {
    this->individuals[i].allocate(nGenes);
		this->individuals[i].randomize();
	}
}

void population::set_target(Pixel* target, int imageSize) {
  // set the target fitness image to calculate the relative fitnesses of all the individual genomes
  this->targetGenome.allocate(imageSize);
  this->target = target;
	for (int i = 0; i < imageSize; i++) {
		this->targetGenome.setPixel(i, target[i]);
	}
}

void population::select_parents() {
  // determine the two overall best individuals in the current population based on their relative fitness
	double parent1Fitness = 100.0;
	double parent2Fitness = 100.0;
	double error;
	for (int i = 0; i < this->nIndividuals; i++) {
    error = this->individuals[i].calculate_overall_fitness(this->target, this->nGenes); 
    cout << "Overall fitness of Individual " << i << ": " << error << endl;
    // if error is smaller than current parent1 fitness, update the index of parent1 and parent2
		if (parent1Fitness > error) {
			parent2Fitness = parent1Fitness;
			parent1Fitness = error;
      this->parent2Index = this->parent1Index;
			this->parent1Index = i;
		}
	}
  // create two arrays of pixel parent1 and parent2 for reference
  if (this->parent1Index != -1) {
    cout << "Parent 1 Index: " << this->parent1Index << endl;
    cout << "Parent 2 Index: " << this->parent2Index << endl; 
    this->parent1 = new Pixel[this->nGenes];
    this->parent2 = new Pixel[this->nGenes];
    for (int i=0; i < this->nGenes; i++) {
      this->parent1[i] = {this->individuals[parent1Index].getRed(i), 
                    this->individuals[parent1Index].getBlue(i), 
                    this->individuals[parent1Index].getGreen(i)};
     
      this->parent2[i] = {this->individuals[parent2Index].getRed(i), 
                    this->individuals[parent2Index].getBlue(i), 
                    this->individuals[parent2Index].getGreen(i)};
    }
 	}
}

void population::set_nCrossover(int nCrossover) {
  // sets the number of crossover points to a positive integer
  if (0 <= this->nCrossover && this->nCrossover < this->nGenes) {
	  this->nCrossover = nCrossover;
  }
}

int population::get_nCrossover() {
  // returns the number of crossover points
	return this->nCrossover;
}

void population::set_mutation(double mRate) {
  // sets the mutation rate of each individual genome to mRate
	for (int i = 0; i < nIndividuals; i++) {
		this->individuals[i].set_mRate(mRate);
	}
}

void population::generate_new_population(int useRoulette=0) {
  // generates the next population
  if (useRoulette == 1) {
    return;
  }
  for (int i = 0; i < this->nIndividuals; i=i+2) {
    for (int j = 0; j < this->nGenes; j++) {
      // if the index of the gene is smaller than crossover point, do not swap
      if (j < this->nCrossover) {
        this->individuals[i].setPixel(j, this->parent1[j]);
        this->individuals[i+1].setPixel(j, this->parent2[j]);
      }
      // swap if the index of gene is greater than crossover
      else {
        this->individuals[i].setPixel(j, this->parent2[j]);
        this->individuals[i+1].setPixel(j, this->parent1[j]);
      }
      // mutate after crossing
      double randNum = (rand()%100)/100.0;
      if (randNum > individuals[i].get_mRate()) {
        individuals[i].mutate();
        individuals[i+1].mutate();
      }
    }
  }
}

double population::calculate_overall_fitness() {
  // returns the average fitness of this population
	double error;
  double sum;
	for (int i = 0; i < this->nIndividuals; i++) {
    error = this->individuals[i].calculate_overall_fitness(this->target, this->nGenes); 
    sum = sum + error;
	}
  double res = sum / this->nIndividuals;
	return res;
}

void population::print_parents() {
  // print out the screen the two parents used to create the next generation
	if (this->parent1Index == -1) {
		cout << "Parents not found" << endl;
	}
	else {
		cout << "Parent 1: ";
    for (int i = 0; i < this->nGenes; i ++) {
      cout << "(" << parent1[i].red << ", " << parent1[i].blue << ", " << parent1[i].green << ") ";
    }
    cout << endl;

		cout << "Parent 2: ";
    for (int i = 0; i < this->nGenes; i ++) {
      cout << "(" << parent2[i].red << ", " << parent2[i].blue << ", " << parent2[i].green << ") ";
    }
    cout << endl;
    cout << endl;
	}
}

void population::print_target() {
  // print out the target
  cout << "TargetGenome: ";
  this->targetGenome.print();
  cout << endl;
}

void population::print_population() {
  // print out the screen the number of crossover points, the mutation rate, and the population
	cout << "Number of crossover: " << this->nCrossover << endl;
	cout << "Mutation rate: " << this->individuals[0].get_mRate() << endl;
	for (int i = 0; i < nIndividuals; i++) {
		cout << "Individual " << i << ": ";
		individuals[i].print();
    cout << endl;
	}
}