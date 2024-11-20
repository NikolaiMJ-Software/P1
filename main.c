#include "connecter.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int input_year;
    char system[10] = "Original";
    printf("Which year do you want to investigate?");
    scanf("%d", &input_year);

    // Get data from year file, and return USA array
    states* USA = ScanData_TXT(input_year);

    // Determine the winner
    char* result = Winner_of_election(USA, system);
    printf("With the %s system, was the winner the %s.\n\n", system, result);

    // User chose a new system
    printf("Chose a new system, STV, PLPR or BC:\n");
    scanf("%s", system);

    // Determine the winner
    result = Winner_of_election(USA, system);
    printf("The winner was the %s, with the %s system.\n\n", result, system);

    free(USA);
    return 0;
}
