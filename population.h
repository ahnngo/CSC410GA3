#include "genome.h"

class population {
  
  public:
    population();        // construction
    ~population();       // destruction
    void generate_population(int popSize, int nGenes); 
    void set_target(Pixel* target, int imageSize);
    void select_parents();
    void set_nCrossover(int nCrossover = 1);
    int get_nCrossover(int nCrossover);
    void set_mutation(double mRate);
    void generate_new_population(int useRoulette);
    double calculate_overall_fitness();
    void print_parents();
    void print_population();
    
  
  private:
    int nIndividuals;
    int *individuals = new int[nIndividuals];
};