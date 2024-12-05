#include "connecter.h"

int main(void) {
    printUSA();
    const char* directory = "US_election_data";
    int counter_CMP = -1;
    // Allocate memory for the array e_systems
    cmp* e_systems = malloc(NO_SYSTEMS * sizeof(cmp));
    if (e_systems == NULL) {
        // Error handling if memory allocation fails
        printf("Memory allocation failed!\n");
        return 1;
    }
    cmp* uncap_systems = malloc(NO_SYSTEMS * sizeof(cmp));
    if (uncap_systems == NULL) {
        // Error handling if memory allocation fails
        printf("Memory allocation failed!\n");
        exit (EXIT_FAILURE);
    }
    // empty both arrays
    memset(e_systems, 0, NO_SYSTEMS * sizeof(cmp));
    memset(uncap_systems, 0, NO_SYSTEMS * sizeof(cmp));
    while(true) {
        int uncapped = 0;
        list_available_files(directory);

        fflush(stdin);
        int input_year;
        char wyoming_rule_true[10];
        char system[10] = "original";
        char abolish_states_true[10];
        int states_abolished = 0;

        // Allocate memory for the array USA
        states* USA = malloc(STATES * sizeof(states));
        if (USA == NULL) {
            // Error handling if memory allocation fails
            printf("Memory allocation failed!\n");
            return 1;
        }

        // Check if cmp e_systems and uncap_systems is full
        int full_e_systems = 0;
        int full_uncap_systems = 0;
        for (int i = 0; i < NO_SYSTEMS; i++) {
            // cap_system
            if (e_systems[i].DEM_electors > 0 || e_systems[i].REP_electors > 0 || e_systems[i].TP_electors > 0) {
                full_e_systems++;
            }
            // uncap system
            if (uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0) {
                full_uncap_systems++;
            }
        }

        // Get data from year file, and return USA array
        int file_loaded = 0; // Variable to track file loading
        while (1) {
            fflush(stdin);
            printf("Which year do you want to investigate?\n");
            scanf("%d", &input_year);
            // If year already simulated and the comparison is full, user try again
            if (input_year == e_systems[0].year && full_e_systems == NO_SYSTEMS && full_uncap_systems == NO_SYSTEMS) {
                printf("The year %d has already been simulated.\n", input_year);
                continue;
            }
            // Check if the year is part of the files
            file_loaded = ScanData_TXT(input_year, USA);
            if (!file_loaded) {
                printf("Invalid year or file not found. Please try again.\n");
            } else {
                break;
            }
        }

        // Insert the year in the cmp system array, empty arrays if different year is entered
        if (counter_CMP > 0 && e_systems[0].year != input_year) {
            memset(e_systems, 0, NO_SYSTEMS * sizeof(cmp));
            memset(uncap_systems, 0, NO_SYSTEMS * sizeof(cmp));
            counter_CMP = 0;
            e_systems[0].year = input_year;
        } else {
            e_systems[0].year = input_year;
            counter_CMP++;
        }

        // Allocate memory for the array candidate_list
        candidates* candidate_list = malloc(CANDIDATES * sizeof(candidates));
        if (candidate_list == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        ScanCandidatesTXT(input_year ,candidate_list);

        //test case
        //parameters(USA, candidate_list, input_year, 0, 1, 0, 0);

        do {
            printf("Would you like to uncap the Electoral College from its current 538 electors (yes/no)\n");
            scanf("%s", &wyoming_rule_true);
            // Clear the input buffer to handle invalid input
            while (getchar() != '\n');
            for (int i = 0; wyoming_rule_true[i] != '\0'; i++) {
                wyoming_rule_true[i] = tolower(wyoming_rule_true[i]);
            }
            if (strcmp(wyoming_rule_true,"no") == 0 && full_e_systems == NO_SYSTEMS) {
                printf("Your choice '%s' has already been simulate for all systems\n", wyoming_rule_true);
                continue;
            }
            if (strcmp(wyoming_rule_true,"yes") == 0 && full_uncap_systems == NO_SYSTEMS) {
                printf("Your choice '%s' has already been simulate for all systems\n", wyoming_rule_true);
                continue;
            }
        } while (strcmp(wyoming_rule_true,"yes") != 0 && strcmp(wyoming_rule_true,"no") != 0);
        if (strcmp(wyoming_rule_true,"yes") == 0) {
            wyoming_rule(input_year, USA);
            uncapped = 1;
        }

        do {
            printf("Would you like to disband all states in the US (yes/no)\n");
            scanf("%s", &abolish_states_true);
            // Clear the input buffer to handle invalid input
            while (getchar() != '\n');
            for (int i = 0; abolish_states_true[i] != '\0'; i++) {
                abolish_states_true[i] = tolower(abolish_states_true[i]);
            }
        } while (strcmp(abolish_states_true,"yes") != 0 && strcmp(abolish_states_true,"no") != 0);
        if (strcmp(abolish_states_true,"yes") == 0) {
            abolish_states(USA);
            states_abolished = 1;
        }

        // Determine the winner
        char* result = Winner_of_election(USA, candidate_list, e_systems, uncap_systems, system, input_year, states_abolished, uncapped);
        printf("With the Electoral college (%s system), the winner was the %s.\n\n", system, result);
        if (counter_CMP == 0) {
            counter_CMP++;
        }
        // User chose a new system
        printf("Chose a new system: STV, PLPR, BC, Custom:\n");
        scanf("%s", system);
        for (int i = 0; system[i] != '\0'; i++) {
            system[i] = toupper(system[i]);
        }
        // Determine the winner
        result = Winner_of_election(USA, candidate_list, e_systems, uncap_systems, system, input_year, states_abolished, uncapped);
        if (strcmp(result, "Custom Done") != 0) {
            printf("The winner was the %s, with the %s system.\n\n", result, system);
        }

        // Compare the tested systems
        if (strcmp(result, "Custom Done") != 0) {
            Compare_table(e_systems, uncap_systems);
        } else {
            memset(e_systems, 0, NO_SYSTEMS * sizeof(cmp));
            memset(uncap_systems, 0, NO_SYSTEMS * sizeof(cmp));
        }

        //ask the user if they wish to see the weight of their vote
        char decide[4];
        do {
            printf("do you wish to see the weight of an electors vote? (yes/no):");
            scanf("%s", &decide);
        }while (strcmp(decide,"yes") != 0 && strcmp(decide,"no") != 0);
        // Exit the loop if the user chooses 'yes'
        if (strcmp(decide,"yes") == 0) {
            weight(USA);
        }
        // Free Arrays
        free(USA);
        free(candidate_list);

        // Ask the user if they want to end the program
        char choice[4];
        do {
            printf("Do you want to end the program? (yes/no):");
            scanf("%s", &choice);

            // Clear the input buffer to handle invalid input
            while (getchar() != '\n');
            for (int i = 0; choice[i] != '\0'; i++) {
                choice[i] = tolower(choice[i]);
            }
        } while (strcmp(choice,"yes") != 0 && strcmp(choice,"no") != 0);
        // Exit the loop if the user chooses 'yes'
        if (strcmp(choice,"yes") == 0) {
            printf("Exiting the program. Goodbye!\n");
            break;
        }
    }
    free(e_systems);
    free(uncap_systems);
    return 0;
}