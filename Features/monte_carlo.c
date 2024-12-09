#include "../connecter.h"
#include <time.h>
#define N_OF_SIMULATIONS 10
#define PERCENT 40 // The chance a DEM will vote for a REP, and the opposite, as second preference

void MC_all(int old_DEM_votes, int old_REP_votes, int old_TP_votes, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes);
void DISTR_DEM(int old_DEM_votes, int* new_REP_votes, int* new_TP_votes);
void DISTR_REP(int old_REP_votes, int* new_DEM_votes, int* new_TP_votes);
void DISTR_TP(int old_TP_votes, int* new_DEM_votes, int* new_REP_votes);

// Make simulations with monte carlo
void monte_carlo(states* USA, int state, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    // Make randomize based on time
    srand(time(NULL));

    // Second preference (0=all, 1=DEM, 2=REP, 3=TP)
    int tot_new_DEM_votes = 0, tot_new_REP_votes = 0, tot_new_TP_votes = 0;
    for (int i = 0; i < N_OF_SIMULATIONS; i++) {
        if (choice == 0) {
            MC_all(USA[state].dem_votes, USA[state].rep_votes, USA[state].third_votes, new_DEM_votes, new_REP_votes, new_TP_votes);
        } else if (choice == 1) {
            DISTR_DEM(USA[state].dem_votes, new_REP_votes, new_TP_votes);
        } else if (choice == 2) {
            DISTR_REP(USA[state].rep_votes, new_DEM_votes, new_TP_votes);
        } else if (choice == 3) {
            DISTR_TP(USA[state].third_votes, new_DEM_votes, new_REP_votes);
        }
        // Add to total votes in the state
        int new_D = *new_DEM_votes;
        int new_R = *new_REP_votes;
        int new_TP = *new_TP_votes;
        tot_new_DEM_votes += new_D;
        tot_new_REP_votes += new_R;
        tot_new_TP_votes += new_TP;
    }
    // Returning the average
    *new_DEM_votes = tot_new_DEM_votes / N_OF_SIMULATIONS;
    *new_REP_votes = tot_new_REP_votes / N_OF_SIMULATIONS;
    *new_TP_votes = tot_new_TP_votes / N_OF_SIMULATIONS;
}

// All voters second preference
void MC_all(int old_DEM_votes, int old_REP_votes, int old_TP_votes,
        int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    // Reset the new votes for all parties
    *new_DEM_votes = 0;
    *new_REP_votes = 0;
    *new_TP_votes = 0;

    // DEM voters second preference
    for(int i = 0; i < old_DEM_votes; i++) {
        // Random choice between REP (PERCENT=40%) and TP (rest)
        int r_no = rand() % 100;
        // Add the vote to the new_party
        if (r_no < PERCENT) {
            (*new_REP_votes)++;
        } else {
            (*new_TP_votes)++;
        }
    }

    // REP voters second preference
    for(int i = 0; i < old_REP_votes; i++) {
        // Random choice between DEM (PERCENT=40%) and TP (rest)
        int r_no = rand() % 100;
        // Add the vote to the new_party
        if (r_no < PERCENT) {
            (*new_DEM_votes)++;
        } else {
            (*new_TP_votes)++;
        }
    }

    // Third parties votes second preference
    for(int i = 0; i < old_TP_votes; i++) {
        // Random choice between DEM (0) and REP (1)
        int r_no = rand() % 2;
        if (r_no) {
            (*new_REP_votes)++;
        } else {
            (*new_DEM_votes)++;
        }
    }
}
void DISTR_DEM(int old_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    // DEM voters second preference
    for(int i = 0; i < old_DEM_votes; i++) {
        // Random choice between REP (PERCENT=40%) and TP (rest)
        int r_no = rand() % 100;
        // Add the vote to the new_party
        if (r_no < PERCENT) {
            (*new_REP_votes)++;
        } else {
            (*new_TP_votes)++;
        }
    }
}
void DISTR_REP(int old_REP_votes, int* new_DEM_votes, int* new_TP_votes) {
    // REP voters second preference
    for(int i = 0; i < old_REP_votes; i++) {
        // Random choice between DEM (PERCENT=40%) and TP (rest)
        int r_no = rand() % 100;
        // Add the vote to the new_party
        if (r_no < PERCENT) {
            (*new_DEM_votes)++;
        } else {
            (*new_TP_votes)++;
        }
    }
}
void DISTR_TP(int old_TP_votes, int* new_DEM_votes, int* new_REP_votes) {
    // Third parties votes second preference
    for(int i = 0; i < old_TP_votes; i++) {
        // Random choice between DEM (0) and REP (1)
        int r_no = rand() % 2;
        if (r_no) {
            (*new_REP_votes)++;
        } else {
            (*new_DEM_votes)++;
        }
    }
}