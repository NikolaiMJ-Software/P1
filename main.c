#include <stdio.h>
#include <stdlib.h>
#include "connecter.h"

int main(void) {
    int input_year;
    printf("Which year do you want to investigate? ");
    scanf("%d", &input_year);

    // Get data from year file
    states* USA = ScanData_TXT(input_year);

    // Determine the winner
    char* result = Winner_of_election(USA);
    printf("The winner was %s\n", result);


    return 0;
}
