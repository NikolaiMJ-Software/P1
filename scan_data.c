#include "connecter.h"

void ScanData_TXT(int input_year, states* USA) {
    char filename[50];
    // insert the input_year in the file name
    snprintf(filename, sizeof(filename), "US_election_data/US_Election_%d.txt", input_year);

    // load the file in read mode and define it as input
    FILE *inputFile = fopen(filename, "r");

    //test if inputfile can load, if not exit failure
    if (!inputFile) {
        perror("File could not open!");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<STATES; i++) {
        //scan inputfile
        fscanf(inputFile, "%[^0-9] %d %lf %lf %d\n",
            USA[i].stateName, &USA[i].electors, &USA[i].democrats, &USA[i].republicans, &USA[i].population);

        // Remove the last character in stateName
        int len = strlen(USA[i].stateName);
        USA[i].stateName[len - 1] = '\0';
    }
    //CLOSE FILE
    fclose(inputFile);
}
