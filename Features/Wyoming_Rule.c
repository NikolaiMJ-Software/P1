#include "../connecter.h"
void wyoming_rule(states* USA, cmp* cap_systems){
    int total_population = 0;
    // Defining the population of Wyoming, as its the last dataset in all data
    int wyoming_population = USA[50].population;
    int new_total_elector_count = 0;
    // Calculating the total population of the US based on the population from each state, and recalculating their new elector amount using the Wyoming rule
    for(int i=0;i<STATES;i++){
        total_population += USA[i].population;
        USA[i].electors = (USA[i].population/wyoming_population)+2;
        new_total_elector_count += USA[i].electors;
    }
    // Buffers to hold formatted numbers
    char tot_pop[30] = "";
    // Return voters with commas
    format_number(total_population, tot_pop);
    printf("The total population for the dataset %d: %s people, which means the new electoral college has %d electors\n", cap_systems[0].year, tot_pop, new_total_elector_count);
}