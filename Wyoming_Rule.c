#include "connecter.h"


states* wyoming_rule(int input_year,states* USA){
    int total_population = 0;
    int wyoming_population = USA[49].population;
    for(int i=0;i<STATES;i++){
        total_population += USA[i].population;
        USA[i].electors = USA[i].population/wyoming_population+2;
    }
    printf("total: %d\n",total_population);
    int new_total_elector_count = total_population/wyoming_population+100;
    printf("The total population for the dataset %d: %d people, which means the new electoral college has %d electors\n",input_year, total_population, new_total_elector_count);
}