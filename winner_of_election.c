#include "connecter.h"

char* Winner_of_election(states* USA, cmp* e_systems, char* system, int input_year, int* counter_CMP) {
    while(true) {
        // Check if the election system has already been calculator
        for (int i = 0; i < NO_E_SYSTEMS; i++) {
            if (strcmp(e_systems[i].system_name, system) == 0) {
                printf("Comparing '%s' with new '%s'\n", e_systems[i].system_name, system);
                *counter_CMP = i;
                printf("%d\n", i);
                printf("%d\n", *counter_CMP);
                printf("The system '%s' has already been calculated, but here is a updated version\n", system);
                break;
            }
        }
        if (strcmp(system, "original") == 0) {
            return electoral_college(USA, e_systems, input_year);
        } else if (strcmp(system, "STV") == 0) {
            return STV(USA, e_systems, 1, *counter_CMP);
        } else if (strcmp(system, "PLPR") == 0) {
            return PLPR(USA, e_systems, *counter_CMP);
        } else if (strcmp(system, "BC") == 0) {
            return BC(USA, e_systems, 1, *counter_CMP);
        } else {
            printf("The chosen election system is not in the database, try again.\n");
            printf("Chose a new system: STV, PLPR, BC:\n");
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
        }
    }
}