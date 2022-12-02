#include "population.h"
#include <iostream>
#include <string>

using namespace std;

population::population() {
	individuals = NULL;
	nIndividuals = 0;
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
	for (int i = 0; i < popSize; i++) {
    this->individuals[i].allocate(nGenes);
		this->individuals[i].randomize();
	}
}

void population::set_target(Pixel* target, int imageSize) {
  this->targetGenome.allocate(imageSize);
	for (int i; i < imageSize; i++) {
		this->targetGenome.setRed(i, target[i].red);
    this->targetGenome.setGreen(i, target[i].green);
    this->targetGenome.setBlue(i, target[i].blue);
	}
}

void population::select_parents() {
	double parent1Fitness = 100.0;
	double parent2Fitness = 100.0;
	for (int i = 0; i < nIndividuals; i++) {
		double error = this->individuals[i].calculate_overall_fitness(targetGenome); // FIX ME ARGUMENT NOT VALID NEED OVERLOADING
		if (parent1Fitness < error) {
			parent2Fitness = parent1Fitness;
			this->parent2 = this->parent1;
			parent1Fitness = error;
			parent1 = this->individuals[i];
		}
	}
}

void population::set_nCrossover(int nCrossover = 1) {
	this->nCrossover = nCrossover;
}

int population::get_nCrossover() {
	return this->nCrossover;
}

void population::set_mutation(double mRate) {
	for (int i = 0; i < nIndividuals; i++) {
		this->individuals[i].set_mRate(mRate);
	}
}

void population::generate_new_population(int useRoulette) {

}

double population::calculate_overall_fitness() {
	double sumFitness;
	for (int i = 0; i < this->nIndividuals; i++) {
		sumFitness += this->individuals[i].calculate_overall_fitness(targetGenome); // // FIX ME ARGUMENT NOT VALID NEED OVERLOADING
	}
  double res = sumFitness / this->nIndividuals;
	return res;
}

void population::print_parents() {
	if (this->parent1.getNGenes() == 0) {
		cout << "Parents not found" << endl;
	}
	else {
		cout << "Parent 1: ";
		this->parent1.print();
		cout << "Parent 2: ";
		this->parent2.print();
	}
}

void population::print_population() {
	cout << "Number of crossover points: " << this->nCrossover << endl;
	cout << "Mutation rate: " << this->individuals[0].get_mRate() << endl;
	for (int i = 0; i < nIndividuals; i++) {
		cout << "Individual " << i << ":";
		individuals[i].print();
	}
}