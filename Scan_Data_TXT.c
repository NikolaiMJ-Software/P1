
#include "Scan_Data_TXT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LGT 14
#define STATES 50
typedef struct states {
    char stateName[NAME_LGT];
    int electors;
    double democrats;
    double republicans;
    int population;
}states;

void ScanData_TXT() {

    FILE *inputFile = fopen("US_Election_2016.txt", "r");
    if (!inputFile) {
        perror("Kunne ikke åbne inputfilen");
        exit(EXIT_FAILURE);
    }

    states USA[STATES];


    for(int i = 0; i<STATES; i++) {

        fscanf(inputFile, "%[^0-9] %d %lf %lf %d\n",
            USA[i].stateName, &USA[i].electors, &USA[i].democrats, &USA[i].republicans, &USA[i].population);

    int len = strlen(USA[i].stateName);
    while (len > 0 && (USA[i].stateName[len - 1] == ' ' || USA[i].stateName[len - 1] == '\n')) {
        USA[i].stateName[len - 1] = '\0';
        len--;
    }
}
    fclose(inputFile);

    for (int i = 0; i < STATES; i++) {
        printf("%s, %d, %.1lf, %.1lf, %d \n", USA[i].stateName, USA[i].electors, USA[i].democrats, USA[i].republicans, USA[i].population);
    }

}
