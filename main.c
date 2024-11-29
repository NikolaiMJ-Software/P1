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
        char wyoming_rule_true = 'n';
        char system[10] = "original";

        // Allocate memory for the array USA
        states* USA = malloc(STATES * sizeof(states));
        if (USA == NULL) {
            // Error handling if memory allocation fails
            printf("Memory allocation failed!\n");
            return 1;
        }

        // Get data from year file, and return USA array
        int file_loaded = 0; // Variable to track file loading
        while (!file_loaded) {
            fflush(stdin);
            printf("Which year do you want to investigate?\n");
            scanf("%d", &input_year);

            file_loaded = ScanData_TXT(input_year, USA);
            if (!file_loaded) {
                printf("Invalid year or file not found. Please try again.\n");
            }
        }

        // Insert the year in the cmp system array, free memory if different year is entered
        if (counter_CMP > 0 && e_systems[0].year != input_year) {
            free(e_systems);
            // Allocate memory for the array e_systems
            cmp* e_systems = malloc(NO_E_SYSTEMS * sizeof(cmp));
            if (e_systems == NULL) {
                // Error handling if memory allocation fails
                printf("Memory allocation failed!\n");
                return 1;
            }
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
            printf("Would you like to uncap the Electoral College from its current 538 electors (y/n)\n");
            scanf(" %c", &wyoming_rule_true);
            // Clear the input buffer to handle invalid input
            while (getchar() != '\n');
            wyoming_rule_true = tolower(wyoming_rule_true);
        } while (wyoming_rule_true != 'y' && wyoming_rule_true != 'n');

        if (wyoming_rule_true == 'y') {
            wyoming_rule(input_year, USA);
        }
        // Determine the winner
        char* result = Winner_of_election(USA, e_systems, system, input_year, counter_CMP);
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
        result = Winner_of_election(USA, e_systems, system, input_year, counter_CMP);
        printf("The winner was the %s, with the %s system.\n\n", result, system);

        // Free Arrays
        free(USA);
        free(candidate_list);

        // Compare the testes systems
        Compare_table(e_systems, counter_CMP);

        // Ask the user if they want to end the program
        char choice;
        do {
            printf("Do you want to end the program? (y/n):");
            scanf(" %c", &choice);

            // Clear the input buffer to handle invalid input
            while (getchar() != '\n');
            choice = tolower(choice);
        } while (choice != 'y' && choice != 'n');
        // Exit the loop if the user chooses 'y'
        if (choice == 'y') {
            printf("Exiting the program. Goodbye!\n");
            break;
        }
    }
    free(e_systems);
    return 0;
}
