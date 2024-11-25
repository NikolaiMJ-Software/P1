#include "connecter.h"
#include <time.h>
#define N_OF_SIMULATIONS 10

void MC_first_case(int TOT_tp_votes, int* new_DEM_votes, int* new_REP_votes, int choice);
void MC_second_case(int TOT_DEM_votes, int TOT_REP_votes, int TOT_TP_votes,
                    int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes, int procent);

// Monte Carlo study of the voters second preference
void monte_carlo(int old_DEM, int old_REP, int old_third, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    // Make the randomize based on the time
    srand(time(NULL));

    int TOT_DEM_votes = 0, TOT_REP_votes = 0, TOT_TP_votes = 0;
    // Calculate the total of the votes, for all parties
    TOT_TP_votes = old_third;
    TOT_DEM_votes = old_DEM;
    TOT_REP_votes = old_REP;
    // Call function, based on users choice
    if (choice == 1) {
        // ONLY third party second preference
        MC_first_case(TOT_TP_votes, new_DEM_votes, new_REP_votes, choice);
    } else if (choice == 2) {
        // User chose the percentage a DEM will vote for a REP, and the opposite, as second preference
        int procent = 40;
        //printf("What percentage chance shod democrats voters chose republicain party as there second choice, and the opposite?\n");
        //scanf("%d", &procent);
        // All second preference
        MC_second_case(TOT_DEM_votes, TOT_REP_votes, TOT_TP_votes,
                      new_DEM_votes, new_REP_votes, new_TP_votes, procent);
    }
}

// CASE 1: if the third-party votes get lost, and have to chose between DEM og REP
void MC_first_case(int TOT_tp_votes, int* new_DEM_votes, int* new_REP_votes, int choice) {
    int DEM_count = 0, REP_count = 0;
    // Reset the new votes for DEM and REP if CASE 1 is chosen
    if (choice == 1) {
        *new_DEM_votes = 0;
        *new_REP_votes = 0;
    }
    // Third parties votes second preference
    for(int i = 0; i < TOT_tp_votes; i++) {
        for(int j = 0; j < N_OF_SIMULATIONS; j++) {
            // Random choice between DEM (1) and REP (0)
            int r_no = rand() % 2;
            if (r_no) {
                DEM_count++;
            } else {
                REP_count++;
            }
        }
        // Add the vote to the party with most amount of votes
        if (DEM_count < REP_count) {
            (*new_REP_votes)++;
        } else {
            (*new_DEM_votes)++;
        }
        DEM_count = 0;
        REP_count = 0;
    }
}

// CASE 2: All voters second preference
void MC_second_case(int TOT_DEM_votes, int TOT_REP_votes, int TOT_TP_votes,
                    int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes, int procent) {
    int DEM_count = 0, REP_count = 0, TP_count = 0;
    // Reset the new votes for all parties
    *new_DEM_votes = 0;
    *new_REP_votes = 0;
    *new_TP_votes = 0;
    // DEM voters second preference
    for(int i = 0; i < TOT_DEM_votes; i++) {
        for(int j = 0; j < N_OF_SIMULATIONS; j++) {
            // Random choice between REP (user %) and TP (rest)
            int r_no = rand() % 100;
            if (r_no < procent) {
                REP_count++;
            } else {
                TP_count++;
            }
        }
        // Add the vote to the party with most amount of votes
        if (TP_count < REP_count) {
            (*new_REP_votes)++;
        } else {
            (*new_TP_votes)++;
        }
        TP_count = 0;
        REP_count = 0;
    }

    // REP voters second preference
    for(int i = 0; i < TOT_REP_votes; i++) {
        for(int j = 0; j < N_OF_SIMULATIONS; j++) {
            // Random choice between DEM (user %) and TP (rest)
            int r_no = rand() % 100;
            if (r_no < procent) {
                DEM_count++;
            } else {
                TP_count++;
            }
        }
        if (TP_count < DEM_count) {
            (*new_DEM_votes)++;
        } else {
            (*new_TP_votes)++;
        }
        // Add the vote to the party with most amount of votes
        TP_count = 0;
        DEM_count = 0;
    }
    // run first case, to find third party second preference
    MC_first_case(TOT_TP_votes, new_DEM_votes, new_REP_votes, 2);
}