#include "connecter.h"

int main(void) {
    int input_year;
    int wyoming_rule_true = 0;
    char system[10] = "Original";
    printf("Which year do you want to investigate?");
    scanf("%d", &input_year);


    states* USA = malloc(STATES * sizeof(states));  // Allocate memory for the array
    if (USA == NULL) {
        // Error handling if memory allocation fails
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Get data from year file, and return USA array
    ScanData_TXT(input_year, USA);
    if (wyoming_rule_true == 0) {
        wyoming_rule(input_year, USA);
    }
    // Determine the winner
    char* result = Winner_of_election(USA, system);
    printf("With the %s system, was the winner the %s.\n\n", system, result);

    // User chose a new system
    printf("Chose a new system: STV, PLPR or BC:\n");
    scanf("%s", system);

    // Determine the winner
    result = Winner_of_election(USA, system);
    printf("The winner was the %s, with the %s system.\n\n", result, system);

    free(USA);
    return 0;
}
