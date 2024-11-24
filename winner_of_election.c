#include "connecter.h"

char* Winner_of_election(states* USA, char* system) {
    while(true) {
        if (strcmp(system, "original") == 0) {
            return electoral_college(USA);
        } else if (strcmp(system, "stv") == 0) {
            return STV(USA);
        } else if (strcmp(system, "plpr") == 0) {
            return PLPR(USA);
        } else if (strcmp(system, "bc") == 0) {
            return BC(USA);
        } else {
            printf("The chosen election system is not in the database, try again.\n");
            printf("Chose a new system: STV, PLPR or BC:\n");
            scanf("%s", system);
        }
    }
}