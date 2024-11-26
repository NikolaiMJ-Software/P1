#include "connecter.h"

int main(void) {
    const char* directory = "US_election_data";

    while(true) {
        list_available_files(directory);

        fflush(stdin);
        int input_year;
        char wyoming_rule_true = 'n';
        char system[10] = "original";


        states* USA = malloc(STATES * sizeof(states));  // Allocate memory for the array
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
        char* result = Winner_of_election(USA, system);
        printf("With the %s system, was the winner the %s.\n\n", system, result);

        // User chose a new system
        printf("Chose a new system: STV, PLPR or BC:\n");
        scanf("%s", system);
        for (int i = 0; system[i] != '\0'; i++) {
            system[i] = tolower(system[i]);
        }

        // Determine the winner
        result = Winner_of_election(USA, system);
        printf("The winner was the %s, with the %s system.\n\n", result, system);

        free(USA);

        // Ask the user if they want to end the program
        char choice;
        do {
            printf("Do you want to end the program? (y/n): ");
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

    return 0;
}
