#include "connecter.h"

int main(void) {
    const char* directory = "US_election_data";
    int counter_CMP = -1, already_calculated;
    // Allocate memory for the array e_systems
    cmp* e_systems = malloc(NO_E_SYSTEMS * sizeof(cmp));
    if (e_systems == NULL) {
        // Error handling if memory allocation fails
        printf("Memory allocation failed!\n");
        return 1;
    }
    while(true) {
        list_available_files(directory);

        fflush(stdin);
        int input_year;
        char wyoming_rule_true[4];
        char system[10] = "original";

        // Allocate memory for the array USA
        states* USA = malloc(STATES * sizeof(states));
        if (USA == NULL) {
            // Error handling if memory allocation fails
            printf("Memory allocation failed!\n");
            return 1;
        }

        // Check if cmp e_systems is full
        int full_e_systems = 1;
        if (strcmp (e_systems[3].system_name, "BC") != 0 &&
            strcmp (e_systems[3].system_name, "PLPR") != 0 &&
            strcmp (e_systems[3].system_name, "STV") != 0) {
            full_e_systems = 0;
        }

        // Get data from year file, and return USA array
        int file_loaded = 0; // Variable to track file loading
        while (1) {
            fflush(stdin);
            printf("Which year do you want to investigate?\n");
            scanf("%d", &input_year);
            // If year already simulated and the comparison is full, user try again
            if (input_year == e_systems[0].year && full_e_systems) {
                printf("The year %d has already been simulated, but you can still update the election systems.\n", input_year);
                //continue;
            }
            // Check if the year is part of the files
            file_loaded = ScanData_TXT(input_year, USA);
            if (!file_loaded) {
                printf("Invalid year or file not found. Please try again.\n");
            } else {
                break;
            }
        }

        // Insert the year in the cmp system array, free memory if different year is entered
        if (counter_CMP > 0 && e_systems[0].year != input_year) {
            memset(e_systems, 0, NO_E_SYSTEMS * sizeof(cmp));
            counter_CMP = 0;
            e_systems[0].year = input_year;
        } else {
            for (int i = 0; i < NO_E_SYSTEMS; i++) {
                e_systems[i].year = input_year;
            }
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
        } while (strcmp(wyoming_rule_true,"yes") != 0 && strcmp(wyoming_rule_true,"no") != 0);
        if (strcmp(wyoming_rule_true,"yes") == 0) {
            wyoming_rule(input_year, USA);
        }
        // Determine the winner
        char* result = Winner_of_election(USA, e_systems, system, input_year, &counter_CMP);
        printf("With the Electoral college (%s system), the winner was the %s.\n\n", system, result);
        if (counter_CMP == 0) {
            counter_CMP++;
        }
        // User chose a new system
        printf("Chose a new system: STV, PLPR, BC:\n");
        scanf("%s", system);
        for (int i = 0; system[i] != '\0'; i++) {
            system[i] = toupper(system[i]);
        }
        // Determine the winner
        result = Winner_of_election(USA, e_systems, system, input_year, &counter_CMP);
        printf("The winner was the %s, with the %s system.\n\n", result, system);

        // Free Arrays
        free(USA);
        free(candidate_list);

        // Compare the tested systems
        Compare_table(e_systems, counter_CMP);

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
    return 0;
}
