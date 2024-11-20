#include <stdio.h>
#include "Scan_Data_TXT.h"




int main(void) {
    int input_year;
    printf("Which year do you want to investigate? ");
    scanf("%d", &input_year);
    // Get data from year file
    ScanData_TXT(input_year);




    return 0;
}
