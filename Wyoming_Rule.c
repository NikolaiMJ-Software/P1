#include "connecter.h"


states* wyoming_rule(int input_year,states* USA){
    int total_population = 0;
    int wyoming_population = USA[50].population;
    int new_total_elector_count = 0;
    for(int i=0;i<STATES;i++){
        total_population += USA[i].population;
        USA[i].electors = (USA[i].population/wyoming_population)+2;
        new_total_elector_count += USA[i].electors;
    }
    printf("The total population for the dataset %d: %d people, which means the new electoral college has %d electors\n",input_year, total_population, new_total_elector_count);
}