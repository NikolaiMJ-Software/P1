#include "connecter.h"

int total_population = 0;

states* wyoming_rule(int input_year,states* USA){
    for(int i=0;i<STATES;i++){
      total_population += USA[i].population;
    }
    printf("Total population = %d\n",total_population);
}