#include "../connecter.h"
void compare_weights(states* USA, double* stateweight);
// Function to print the weight for an elector from each state
void weight(states* USA, int* first_run) {

    if (USA == NULL) {
        printf("Error: USA array is NULL.\n");
        return;
    }

    double stateweight[STATES];
    int totalElectors = 0;

    printf("\nEach state has a given number of electors for the Electoral College. This number is decided by the state's population,  where each state has at least three electors (two from Senators).\n"
           "But what is the weight of the votes for each state? That can be observed below, sorted from most to least weight with   weight being defined as population divided by the amount of electors in the state:\n\n");
    if (first_run == 0) {
        sleep(10);
    } else {
    // Nothing
    }
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
    printf("||--------------------------------------------------------------------------------------------------------||\n");
    printf("||State                 Weight                   Electors          Percentage             Population      ||\n");
    printf("||--------------------------------------------------------------------------------------------------------||\n");

    // Print the sorted states and their weights
    for (int i = 0; i < STATES; i++) {
        // Convert double array to int array
        int int_stateweight = (int)stateweight[i];
        int int_pop= USA[i].population;
        // Buffers to hold formatted numbers
        char weight[30] = "";
        char pop[30] = "";
        // Return voters with commas
        format_number(int_stateweight, weight);
        format_number(int_pop, pop);

        double statePercentage = (double)USA[i].electors / totalElectors * 100;
        printf("||%-20s: Weight = %s,       Electors = %2d (%5.2f%% of total),  Population = %10s ||\n",
               USA[i].stateName, weight, USA[i].electors, statePercentage, pop);
    }

    printf("||--------------------------------------------------------------------------------------------------------||\n");
    printf("\nWeight represents the number of voters each elector represents. Percentage shows each state's contribution to the total Electoral College.\n\n");
    *first_run = 1;
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