#include "connecter.h"
#include <time.h>
#define N_OF_SIMULATIONS 50000

void MC_first_case(int TOT_tp_votes, int* new_DEM_votes, int* new_REP_votes);
void MC_second_case(int TOT_DEM_votes, int TOT_REP_votes, int TOT_TP_votes,
                    int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes);

// Monte Carlo study of the voters second preference
void monte_carlo(states* USA, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    // Make thE randomize based on the time
    srand(time(NULL));

    int TOT_DEM_votes = 0, TOT_REP_votes = 0, TOT_TP_votes = 0;
    // Calculate the total of the votes, for all parties
    for (int i = 0; i < STATES; i++) {
        TOT_TP_votes += USA[i].third_votes;
        TOT_DEM_votes += USA[i].dem_votes;
        TOT_REP_votes += USA[i].rep_votes;
    }
    // Call function, based on users choice
    if (choice == 1) {
        // ONLY third party second preference
        MC_first_case(TOT_TP_votes, new_DEM_votes, new_REP_votes);
    } else if (choice == 2) {
        // All second preference
        MC_second_case(TOT_DEM_votes, TOT_REP_votes, TOT_TP_votes,
                      new_DEM_votes, new_REP_votes, new_TP_votes);
    }
}

// CASE 1: if the third-party votes get lost, and have to chose between DEM og REP
void MC_first_case(int TOT_tp_votes, int* new_DEM_votes, int* new_REP_votes) {
    int DEM_count = 0, REP_count = 0;
    // Reset the new votes for DEM and REP
    *new_DEM_votes = 0;
    *new_REP_votes = 0;
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
                    int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    int D_count = 0, R_count = 0, TP_count = 0;
    // Reset the new votes for all parties
    *new_DEM_votes = 0;
    *new_REP_votes = 0;
    *new_TP_votes = 0;
    // DEM voters second preference
    for(int i = 0; i < TOT_DEM_votes; i++) {
        for(int j = 0; j < N_OF_SIMULATIONS; j++) {
            // Random choice between REP (0) and TP (1,2)
            int r_no = rand() % 3;
            if (r_no == 0) {
                R_count++;
            } else {
                TP_count++;
            }
        }
        // Add the vote to the party with most amount of votes
        if (TP_count < R_count) {
            (*new_REP_votes)++;
        } else {
            (*new_TP_votes)++;
        }
        TP_count = 0;
        R_count = 0;
    }

    D_count = 0, TP_count = 0;
    // REP voters second preference
    for(int i = 0; i < TOT_REP_votes; i++) {
        for(int j = 0; j < N_OF_SIMULATIONS; j++) {
            // Random choice between DEM (0) and TP (1,2)
            int r_no = rand() % 3;
            if (r_no == 3) {
                D_count++;
            } else {
                TP_count++;
            }
        }
        if (TP_count < D_count) {
            (*new_DEM_votes)++;
        } else {
            (*new_TP_votes)++;
        }
        // Add the vote to the party with most amount of votes
        TP_count = 0;
        D_count = 0;
    }
    // run first case, to find third party second preference
    MC_first_case(TOT_TP_votes, new_DEM_votes, new_REP_votes);
}