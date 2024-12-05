#include "connecter.h"

char* Winner_of_election(states* USA, candidates* candidate_list, cmp* e_systems, cmp* uncap_systems, char* system, int input_year, int states_abolished, int uncapped) {
    while(true) {
        // Check if the election system has already been calculator
        int already_calculated = 0, counter_cap = 0, counter_uncap = 0;
        if (uncapped) {
            // Uncap_system
            for (int i = 0; i < NO_SYSTEMS; i++) {
                int full_data = uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0;
                if (strcmp(uncap_systems[i].system_name, system) != 0) {
                    if (!full_data && strlen(uncap_systems[i].system_name) == 0) {
                        break;
                    }
                    counter_uncap++;
                } else if (full_data){
                    counter_uncap++;
                    break;
                }
            }
            for (int i = 0; i < NO_SYSTEMS; i++) {
                if (strcmp(uncap_systems[i].system_name, system) == 0 && (uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0)) {
                    already_calculated = 1;
                    break;
                }
            }
        } else {
            // Normal_systems
            for (int i = 0; i < NO_SYSTEMS; i++) {
                int full_data = e_systems[i].DEM_electors > 0 || e_systems[i].REP_electors > 0 || e_systems[i].TP_electors > 0;
                if (strcmp(e_systems[i].system_name, system) != 0) {
                    if (!full_data && strlen(e_systems[i].system_name) == 0) {
                        break;
                    }
                    counter_cap++;
                } else if (full_data){
                    counter_cap++;
                    break;
                }
            }
            for (int i = 0; i < NO_SYSTEMS; i++) {
                if (strcmp(e_systems[i].system_name, system) == 0 && (e_systems[i].DEM_electors > 0 || e_systems[i].REP_electors > 0 || e_systems[i].TP_electors > 0)) {
                    already_calculated = 1;
                    break;
                }
            }
        }
        printf("CAP: %d\n", counter_cap);
        printf("UNCAP: %d\n\n\n\n\n\n", counter_uncap);
        // Print an error message to the user
        if (already_calculated) {
            printf("The system '%s' has already been calculated\n", system);
            printf("Chose a new system: STV, PLPR, BC:\n");
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
            // Start from the beginning of the while loop
            continue;
        }

        if (strcmp(system, "original") == 0) {
            return electoral_college(USA, e_systems, uncap_systems, input_year, uncapped);
        } else if (strcmp(system, "STV") == 0) {
            return STV(USA, e_systems, uncap_systems, 1, counter_cap, counter_uncap, states_abolished, uncapped);
        } else if (strcmp(system, "PLPR") == 0) {
            return PLPR(USA, e_systems, uncap_systems, counter_cap, counter_uncap, uncapped);
        } else if (strcmp(system, "BC") == 0) {
            return BC(USA, e_systems, uncap_systems, 1, counter_cap, counter_uncap, uncapped);
        } else if (strcmp(system, "Custom")) {
            parameters(USA, candidate_list, input_year);
            return "Custom Done";
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