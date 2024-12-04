#include "connecter.h"
#include <stdio.h>

void compare_weights(states* USA, double* stateweight);

void weight(states* USA) {
    if (USA == NULL) {
        printf("Error: USA array is NULL.\n");
        return;
    }

    double stateweight[STATES];
    int totalElectors = 0;


    printf("Each state has a given number of electors for the Electoral College. This number is decided by the state's population, where each state has at least three electors (two from Senators).\n");
    printf("But what is the weight of the votes for each state? That can be observed below, sorted from most to least weight:\n\n");

    // Calculate weights and validate data

    for (int i = 0; i < STATES; i++) {
        if (USA[i].stateName == NULL || USA[i].electors <= 0 || USA[i].population <= 0) {
            printf("Error: Invalid data for state %d.\n", i);
            return; // Stop execution if invalid data is found
        }
        stateweight[i] = (double)USA[i].population / USA[i].electors;
    }

    // Sort the states by weight
    compare_weights(USA, stateweight);

    // Calculate the total number of electors
    for (int i = 0; i < STATES; i++) {
        totalElectors += USA[i].electors;
    }

    // Print the header
    printf("\nWeight in this case shows how many voters each elector represents, thereby how weighty their position is.\n");
    printf("But what is the percentage of a single elector when faced with the whole country?\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("State                 Weight             Electors          Percentage     Population\n");
    printf("--------------------------------------------------------------------------------------------------\n");

    // Print the sorted states and their weights
    for (int i = 0; i < STATES; i++) {
        double statePercentage = (double)USA[i].electors / totalElectors * 100;
        printf("%-20s: Weight = %8.0f, Electors = %2d (%5.2f%% of total), Population = %9d\n",
               USA[i].stateName, stateweight[i], USA[i].electors, statePercentage, USA[i].population);
    }

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("\nWeight represents the number of voters each elector represents. Percentage shows each state's contribution to the total Electoral College.\n\n");
}

void compare_weights(states* USA, double* stateweight) {
    // Perform a bubble sort on state weights and align the USA array
    for (int i = 0; i < STATES - 1; i++) {
        for (int j = 0; j < STATES - i - 1; j++) {
            if (stateweight[j] < stateweight[j + 1]) {
                // Swap weights
                double temp_weight = stateweight[j];
                stateweight[j] = stateweight[j + 1];
                stateweight[j + 1] = temp_weight;

                // Swap corresponding states
                states temp_state = USA[j];
                USA[j] = USA[j + 1];
                USA[j + 1] = temp_state;
            }
        }
    }
}
