#include "connecter.h"

char* Winner_of_election(states* USA, cmp* e_systems, char* system, int input_year, int* counter_CMP, int states_abolished, int uncapped) {
    while(true) {
        // Check if the election system has already been calculator
        int already_calculated = 0;
        if (uncapped) {
            // Uncap_system
            for (int i = 0; i < NO_SYSTEMS; i++) {
                if (strcmp(uncap_systems[i].system_name, system) == 0) {
                    already_calculated = 1;
                    break;
                }
            }
        } else {
            // Normal_systems
            for (int i = 0; i < NO_SYSTEMS; i++) {
                if (strcmp(e_systems[i].system_name, system) == 0) {
                    already_calculated = 1;
                    break;
                }
            }
        }

        // Print an error message to the user
        if (already_calculated) {
            printf("The system '%s' has already been calculated\n", system);
            printf("Chose a new system: STV, PLPR, BC:\n");
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
            // Stat form teh beginning of the while loop
            continue;
        }

        if (strcmp(system, "original") == 0) {
            return electoral_college(USA, e_systems, uncap_systems, input_year, uncapped);
        } else if (strcmp(system, "STV") == 0) {
            return STV(USA, e_systems, 1, *counter_CMP, states_abolished, uncapped);
        } else if (strcmp(system, "PLPR") == 0) {
            return PLPR(USA, e_systems, uncap_systems, *counter_CMP, uncapped);
        } else if (strcmp(system, "BC") == 0) {
            return BC(USA, e_systems, uncap_systems, 1, *counter_CMP, uncapped);
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