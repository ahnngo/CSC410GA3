#include "genome.h"

class population {
  
  public:
    population();        // construction
    ~population();       // destruction
    void generate_population(int popSize, int nGenes); // create a population of popSize individuals, each of which have nGenes genes
    void set_target(Pixel* target, int imageSize); // set the target fitness image to calculate the relative fitnesses of all the individual genomes
    void select_parents(); // determine the two overall best individuals in the current population based on their relative fitness
    void set_nCrossover(int nCrossover); // sets the number of crossover points to a positive integer
    int get_nCrossover(); // returns the number of crossover points
    void set_mutation(double mRate); // sets the mutation rate of each individual genome to mRate
    void generate_new_population(int useRoulette); // generates the next population
    double calculate_overall_fitness(); // returns the average fitness of this population
    void print_parents(); // print out the screen the two parents used to create the next generation
    void print_target(); // print out the target
    void print_population(); // print out the screen the number of crossover points, the mutation rate, and the population
    
  
  private:
    int nIndividuals;
    genome* individuals;
    int nCrossover;
    genome targetGenome;
    Pixel* target;
    int nGenes;
    int parent1Index;
    int parent2Index;
    Pixel* parent1;
    Pixel* parent2;
};