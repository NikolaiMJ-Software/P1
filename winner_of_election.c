#include "connecter.h"
void calc_counter(cmp* cap_systems, cmp* uncap_systems, char* system, int* counter_cap, int* counter_uncap, int uncapped);
int already_calc(cmp* cap_systems, cmp* uncap_systems, char* system, int uncapped);

char* Winner_of_election(states* USA, candidates* candidate_list, cmp* cap_systems, cmp* uncap_systems, char* system, int uncapped, int states_abolished, int from_compare_table) {
    while(true) {
        int already_calculated = 0, counter_cap = 0, counter_uncap = 0;
        // Check if the election system has already been calculator, no need to double-check if Winner_of_election is called from_compare_table or states is abolished
        if (from_compare_table || states_abolished) {
            // Nothing
        } else {
            already_calculated = already_calc(cap_systems, uncap_systems, system, uncapped);
        }
        // Print an error message to the user, if uncap or cap system is already calculator
        if (already_calculated) {
            printf("The system '%s' has already been calculated\n", system);
            printf("Chose a new system: STV, PLPR, BC, Custom or All\nor write 'INFO' for further information:\n");
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
            // Start from the beginning of the while loop
            continue;
        }
        // Calculate the correct place in the array
        calc_counter(cap_systems, uncap_systems, system, &counter_cap, &counter_uncap, uncapped);
        // Return the result from the 4 system based on what the input is
        if (strcmp(system, "original") == 0) {
            return electoral_college(USA, cap_systems, uncap_systems, uncapped, states_abolished);
        } else if (strcmp(system, "STV") == 0) {
            return STV(USA, cap_systems, uncap_systems, 1, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "PLPR") == 0) {
            return PLPR(USA, cap_systems, uncap_systems, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "BC") == 0) {
            return BC(USA, cap_systems, uncap_systems, 1, counter_cap, counter_uncap, uncapped, states_abolished);
        } else if (strcmp(system, "CUSTOM") == 0) {
            int input_year = cap_systems[0].year;
            parameters(USA, candidate_list, input_year, states_abolished);
            return "Custom Done";
        } else if (strcmp(system, "ALL") == 0 && !states_abolished) {
            char decide[4];
            do {
                printf("It could take up to 1 min, are you sure? (yes/no):");
                scanf("%s", &decide);
                printf("\n");
                while (getchar() != '\n');
                for (int i = 0; decide[i] != '\0'; i++) {
                    decide[i] = tolower(decide[i]);
                }
            }while (strcmp(decide,"yes") != 0 && strcmp(decide,"no") != 0 && strcmp(decide,"y") != 0 && strcmp(decide,"n") != 0);
            // Exit the loop if the user chooses 'yes'
            if (strcmp(decide,"yes") == 0 || strcmp(decide,"y") == 0) {
                Compare_table(USA, candidate_list, cap_systems, uncap_systems, 1);
                return "All systems";
            } else {
                // If "no/n", restart the prompt by continuing the loop
                printf("Chose a new system: STV, PLPR, BC, Custom or all\nor write 'INFO' for further information:\n");
                scanf("%s", system);
                // Convert system input to uppercase
                for (int i = 0; system[i] != '\0'; i++) {
                    system[i] = toupper(system[i]);
                }
                // Restart the while loop
                continue;
            }
        } else if (strcmp(system, "INFO") == 0) {
            // Print information links
            printf("Single Transferable Vote (STV): https://www.electoral-reform.org.uk/voting-systems/types-of-voting-system/single-transferable-vote/\n");
            printf("Party List Proportional Representation (PLPR): https://www.electoral-reform.org.uk/voting-systems/types-of-voting-system/party-list-pr/\n");
            printf("Borda Count (BC): https://crawford.anu.edu.au/pdf/staff/ben_reilly/ReillyB_05.pdf\n");
            printf("Custom: Follow Gallagher and Mitchell core values\n");
            printf("All: Test all systems both cap and uncap\n\n");
            // Error message if the system does not exist
            printf("Chose a new system: STV, PLPR, BC, Custom or All\nor write 'INFO' for further information:\n");
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
        } else {
            // Error message if the system does not exist
            if (strcmp(system, "ALL") == 0 && states_abolished) {
                printf("The chosen system 'All' is not possible when the states are abolished, try again.\n");
                printf("Chose a new system: STV, PLPR, BC or Custom\nor write 'INFO' for further information:\n");
            } else {
                printf("The chosen election system is not in the database, try again.\n");
                printf("Chose a new system: STV, PLPR, BC, Custom or all\nor write 'INFO' for further information:\n");
            }
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
        }
    }
}
// Check if the system is already calculator
int already_calc(cmp* cap_systems, cmp* uncap_systems, char* system, int uncapped) {
    if (uncapped) {
        // Check if the uncap_system is already calculator
        for (int i = 0; i < NO_SYSTEMS; i++) {
            if (strcmp(uncap_systems[i].system_name, system) == 0 && (uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0)) {
                return 1;
            }
        }
    } else {
        // Check if the cap_system is already calculator
        for (int i = 0; i < NO_SYSTEMS; i++) {
            if (strcmp(cap_systems[i].system_name, system) == 0 && (cap_systems[i].DEM_electors > 0 || cap_systems[i].REP_electors > 0 || cap_systems[i].TP_electors > 0)) {
                return 1;
            }
        }
    }
    return 0;
}

void calc_counter(cmp* cap_systems, cmp* uncap_systems, char* system, int* counter_cap, int* counter_uncap, int uncapped) {
    if (uncapped) {
        // Uncap_system
        for (int i = 0; i < NO_SYSTEMS; i++) {
            int full_data = uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0;
            // If there is no data and no name to the array, then break, else counter +1
            if (!full_data && strlen(uncap_systems[i].system_name) == 0) {
                break;
            } else {
                (*counter_uncap)++;
            }
            // If the array is not full and "input system" equal to the array system, counter = to the system place in the array (i)
            if (!full_data && strcmp(uncap_systems[i].system_name, system) == 0){
                *counter_uncap = i;
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
                (*counter_cap)++;
            }
            // If the array is not full and "input system" equal to the array system, counter = to the system place in the array (i)
            if (!full_data && strcmp(cap_systems[i].system_name, system) == 0){
                *counter_cap = i;
                break;
            }
        }
    }
}
