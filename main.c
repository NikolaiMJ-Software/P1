#include <stdio.h>
#include "Scan_Data_TXT.h"

int main(void) {
    int input_year;
    printf("Which year do you want to investigate? ");
    scanf("%d", &input_year);
    // Get data from year file
    ScanData_TXT(input_year);

    // The winner was
    char result[10] = Winner_of_election();
    printf("The winner was %s", result);

    return 0;
}
