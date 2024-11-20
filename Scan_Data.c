#include "connecter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

states* ScanData_TXT(input_year) {
    char filename[25];
    // insert the input_year in the file name
    snprintf(filename, sizeof(filename), "US_Election_%d.txt", input_year);

    // load the file in read mode and define it as input
    FILE *inputFile = fopen(filename, "r");

    //test if inputfile can load, if not exit failure
    if (!inputFile) {
        perror("File could not open!");
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
    return USA;
}
