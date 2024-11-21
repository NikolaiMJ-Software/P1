#include "connecter.h"

char* Winner_of_election(states* USA, char* system) {
    if (strcmp(system, "Original") == 0) {
        return electoral_college(USA);
    } else if (strcmp(system, "STV") == 0) {
        return STV(USA);
    } else if (strcmp(system, "PLPR") == 0) {
        return PLPR(USA);
    } else if (strcmp(system, "BC") == 0) {
        return BC(USA);
    } else {
        printf("The chosen election system is not in the database.\n");
        exit(EXIT_FAILURE);
    }
}