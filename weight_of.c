#include "connecter.h"
#include <stdio.h>

// Forward declaration of the sorting function
void compare_weights(states* USA, double* stateweight);

void weight(states* USA){
    if (USA == NULL) {
        printf("Error: USA array is NULL.\n");
        return;
    }
    double stateweight[STATES];
    int total = 0;

    printf("Each state has a given number of electors for the Electoral College. This number is decided by the state's population, where each state has at least three electors (two from Senators).\n");
    printf("But what is the weight of the votes for each state? That can be observed below, sorted from most to least weight:\n\n");

    // Calculate weights for each state
    for (int i = 0; i < STATES; i++) {
        stateweight[i] = (double)USA[i].population / USA[i].electors;
    }

    // Sort the states by weight
    compare_weights(USA, stateweight);

    // Print the sorted states and their weights
    for (int i = 0; i < STATES; i++) {
        printf("\n---%s: Weight = %.0f Electors = %d, Population = %d---\n",
               USA[i].stateName, stateweight[i], USA[i].electors, USA[i].population);
    }
    printf("\nweight in this case shows how many voters each elector represents, thereby how weighty their position is"
           "\nbut what is the percentage of a single elector when faced with the whole country?\n"
           "_________________________________________\n\n");

    for(int i = 0; i < STATES; i++) {
        total += USA[i].electors;
    }
    int percentage = 1 / total * 100;
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
