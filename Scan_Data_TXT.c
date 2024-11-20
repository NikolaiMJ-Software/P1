
#include "Scan_Data_TXT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LGT 14
#define STATES 50
//creation of the states struct
typedef struct states {
    char stateName[NAME_LGT];
    int electors;
    double democrats;
    double republicans;
    int population;
}states;

void ScanData_TXT() {
    // load the file in read mode and define it as input
    FILE *inputFile = fopen("US_Election_2016.txt", "r");
    //test if inputfile can load, if not exit failure
    if (!inputFile) {
        perror("Kunne ikke åbne inputfilen");
        exit(EXIT_FAILURE);
    }
    // define the struct as USA and set the size to the number of states
    states USA[STATES];


    for(int i = 0; i<STATES; i++) {
        //scan inputfile
        fscanf(inputFile, "%[^0-9] %d %lf %lf %d\n",
            USA[i].stateName, &USA[i].electors, &USA[i].democrats, &USA[i].republicans, &USA[i].population);

        // trim the last space from stateName
        int len = strlen(USA[i].stateName);
        while (len > 0 && (USA[i].stateName[len - 1] == ' ' || USA[i].stateName[len - 1] == '\n')) {
            USA[i].stateName[len - 1] = '\0';
            len--;
        }
    }
    //CLOSE FILE
    fclose(inputFile);
}
