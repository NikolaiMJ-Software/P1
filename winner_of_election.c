#include "connecter.h"

char* Winner_of_election(states* USA, candidates* candidate_list, cmp* cap_systems, cmp* uncap_systems, char* system, int input_year, int uncapped, int states_abolished) {
    while(true) {
        // Check if the election system has already been calculator
        int already_calculated = 0, counter_cap = 0, counter_uncap = 0;
        if (uncapped) {
            // Uncap_system
            for (int i = 0; i < NO_SYSTEMS; i++) {
                int full_data = uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0;
                // If there is no data and no name to the array, then break, else counter +1
                if (!full_data && strlen(uncap_systems[i].system_name) == 0) {
                    break;
                } else {
                    counter_uncap++;
                }
                // If the array is not full and "input system" equal to the array system, counter = to the system place in the array (i)
                if (!full_data && strcmp(uncap_systems[i].system_name, system) == 0){
                    counter_uncap = i;
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
                int full_data = cap_systems[i].DEM_electors > 0 || cap_systems[i].REP_electors > 0 || cap_systems[i].TP_electors > 0;
                // If there is no data and no name to the array, then break, else counter +1
                if (!full_data && strlen(cap_systems[i].system_name) == 0) {
                    break;
                } else {
                    counter_cap++;
                }
                // If the array is not full and "input system" equal to the array system, counter = to the system place in the array (i)
                if (!full_data && strcmp(cap_systems[i].system_name, system) == 0){
                    counter_cap = i;
                    break;
                }
            }
            // Check if the cap_system is already calculator
            for (int i = 0; i < NO_SYSTEMS; i++) {
                if (strcmp(cap_systems[i].system_name, system) == 0 && (cap_systems[i].DEM_electors > 0 || cap_systems[i].REP_electors > 0 || cap_systems[i].TP_electors > 0)) {
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
            return electoral_college(USA, cap_systems, uncap_systems, input_year, uncapped, states_abolished);
        } else if (strcmp(system, "STV") == 0) {
            return STV(USA, cap_systems, uncap_systems, 1, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "PLPR") == 0) {
            return PLPR(USA, cap_systems, uncap_systems, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "BC") == 0) {
            return BC(USA, cap_systems, uncap_systems, 1, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "Custom") == 0) {
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