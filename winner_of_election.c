#include "connecter.h"

char* Winner_of_election(states* USA, candidates* candidate_list, cmp* e_systems, cmp* uncap_systems, char* system, int input_year, int uncapped, int states_abolished) {
    while(true) {
        // Check if the election system has already been calculator
        int already_calculated = 0, counter_cap = 0, counter_uncap = 0;
        if (uncapped) {
            // Uncap_system
            for (int i = 0; i < NO_SYSTEMS; i++) {
                int full_data = uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0;
                // If the "input system" in not the system in the array
                if (strcmp(uncap_systems[i].system_name, system) != 0) {
                    // If there is no data in the array and the "input system" equal to the array system, then break, else counter +1
                    if (!full_data && strlen(uncap_systems[i].system_name) == 0) {
                        break;
                    }
                    counter_uncap++;
                // Else if the array is full and "input system" equal to the array system, counter +1 then break
                } else if (full_data){
                    counter_uncap++;
                    break;
                }
            }
            // Check if the uncap_system is already calculator
            for (int i = 0; i < NO_SYSTEMS; i++) {
                if (strcmp(uncap_systems[i].system_name, system) == 0 && (uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0)) {
                    already_calculated = 1;
                    break;
                }
            }
        } else {
            // Cap_systems
            for (int i = 0; i < NO_SYSTEMS; i++) {
                int full_data = e_systems[i].DEM_electors > 0 || e_systems[i].REP_electors > 0 || e_systems[i].TP_electors > 0;
                // If the "input system" in not the system in the array
                if (strcmp(e_systems[i].system_name, system) != 0) {
                    // If there is no data in the array and the "input system" equal to the array system, then break, else counter +1
                    if (!full_data && strlen(e_systems[i].system_name) == 0) {
                        break;
                    }
                    counter_cap++;
                // Else if the array is full and "input system" equal to the array system, counter +1 then break
                } else if (full_data){
                    counter_cap++;
                    break;
                }
            }
            // Check if the cap_system is already calculator
            for (int i = 0; i < NO_SYSTEMS; i++) {
                if (strcmp(e_systems[i].system_name, system) == 0 && (e_systems[i].DEM_electors > 0 || e_systems[i].REP_electors > 0 || e_systems[i].TP_electors > 0)) {
                    already_calculated = 1;
                    break;
                }
            }
        }
        // Print an error message to the user, if ether uncap or cap system is already calculator
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
        // Return the result from the 4 system based on what the input is
        if (strcmp(system, "original") == 0) {
            return electoral_college(USA, e_systems, uncap_systems, input_year, uncapped, states_abolished);
        } else if (strcmp(system, "STV") == 0) {
            return STV(USA, e_systems, uncap_systems, 1, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "PLPR") == 0) {
            return PLPR(USA, e_systems, uncap_systems, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "BC") == 0) {
            return BC(USA, e_systems, uncap_systems, 1, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "Custom")) {
            parameters(USA, candidate_list, input_year);
            return "Custom Done";
        } else {
            // Error message if the system does not exist
            printf("The chosen election system is not in the database, try again.\n");
            printf("Chose a new system: STV, PLPR, BC:\n");
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
        }
    }
}