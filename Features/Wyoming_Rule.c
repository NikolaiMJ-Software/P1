#include "../connecter.h"


//wyoming rule (https://elections-daily.com/2021/06/25/can-the-wyoming-rule-improve-representation/ & https://www.amacad.org/ourcommonpurpose/enlarging-the-house/section/5)
void wyoming_rule(states* USA, cmp* cap_systems){
    int total_population = 0;
    //defining the population of Wyoming, as its the last dataset in all data
    int wyoming_population = USA[50].population;
    int new_total_elector_count = 0;
    //calculating the total population of the US based on the population from each state, and recalculating their new elector amount using the Wyoming rule
    for(int i=0;i<STATES;i++){
        total_population += USA[i].population;
        USA[i].electors = (USA[i].population/wyoming_population)+2;
        new_total_elector_count += USA[i].electors;
    }
    printf("The total population for the dataset %d: %d people, which means the new electoral college has %d electors\n", cap_systems[0].year, total_population, new_total_elector_count);
}

