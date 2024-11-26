#include "connecter.h"
#include <time.h>
#define N_OF_SIMULATIONS 10

void MC_first_case(int TOT_tp_votes, int* new_DEM_votes, int* new_REP_votes, int choice);
void MC_second_case(int old_DEM_votes, int old_REP_votes, int old_TP_votes,
                    int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes, int procent);


// Make simulations on monte carlo, then take the average. Instead simulations on every election, as it is above

void monte_carlo(states* USA, int state, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    // Make the randomize based on the time
    srand(time(NULL));
    // Call function, based on users choice
    if (choice == 1) {
        int tot_new_DEM_votes = 0, tot_new_REP_votes = 0;
        // ONLY third party second preference
        for (int i = 0; i < N_OF_SIMULATIONS; i++) {
            MC_first_case(USA[state].third_votes, new_DEM_votes, new_REP_votes, choice);
            int new_D = *new_DEM_votes;
            int new_R = *new_REP_votes;
            tot_new_DEM_votes += new_D;
            tot_new_REP_votes += new_R;
        }
        // Returning the average
        *new_DEM_votes = tot_new_DEM_votes / N_OF_SIMULATIONS;
        *new_REP_votes = tot_new_REP_votes / N_OF_SIMULATIONS;
    } else if (choice == 2) {
        // User chose the percentage a DEM will vote for a REP, and the opposite, as second preference
        int procent = 40;
        //printf("What percentage chance shod democrats voters chose republicain party as there second choice, and the opposite?\n");
        //scanf("%d", &procent);

        // All second preference
        int tot_new_DEM_votes = 0, tot_new_REP_votes = 0, tot_new_TP_votes = 0;
        // ONLY third party second preference
        for (int i = 0; i < N_OF_SIMULATIONS; i++) {
            MC_second_case(USA[state].dem_votes, USA[state].rep_votes, USA[state].third_votes,
                      new_DEM_votes, new_REP_votes, new_TP_votes, procent);
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
}

// CASE 1: if the third-party votes get lost, and have to chose between DEM og REP
void MC_first_case(int old_tp_votes, int* new_DEM_votes, int* new_REP_votes, int choice) {
    // Reset the new votes for DEM and REP if CASE 1 is chosen
    if (choice == 1) {
        *new_DEM_votes = 0;
        *new_REP_votes = 0;
    }
    // Third parties votes second preference
    for(int i = 0; i < old_tp_votes; i++) {
        // Random choice between DEM (0) and REP (1)
        int r_no = rand() % 2;
        if (r_no) {
            (*new_REP_votes)++;
        } else {
            (*new_DEM_votes)++;
        }
    }
}

// CASE 2: All voters second preference
void MC_second_case(int old_DEM_votes, int old_REP_votes, int old_TP_votes,
                    int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes, int procent) {
    // Reset the new votes for all parties
    *new_DEM_votes = 0;
    *new_REP_votes = 0;
    *new_TP_votes = 0;
    // DEM voters second preference
    for(int i = 0; i < old_DEM_votes; i++) {
        // Random choice between REP (user %) and TP (rest)
        int r_no = rand() % 100;
        // Add the vote to the new_party
        if (r_no < procent) {
            (*new_REP_votes)++;
        } else {
            (*new_TP_votes)++;
        }
    }

    // REP voters second preference
    for(int i = 0; i < old_REP_votes; i++) {
        // Random choice between DEM (user %) and TP (rest)
        int r_no = rand() % 100;
        // Add the vote to the new_party
        if (r_no < procent) {
            (*new_DEM_votes)++;
        } else {
            (*new_TP_votes)++;
        }
    }
    // run first case, to find third party second preference
    MC_first_case(old_TP_votes, new_DEM_votes, new_REP_votes, 2);
}


/*
// Monte Carlo study of the voters second preference
void monte_carlo(states* USA, int state, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes) {
    // Make the randomize based on the time
    srand(time(NULL));
    // Calculate the total of the votes, for all parties
    int TOT_TP_votes = 0, old_DEM_votes = 0, old_REP_votes = 0, old_tp_votes = 0;
    for (int i = 0; i < STATES; i++) {
        TOT_TP_votes += USA[i].third_votes;
    }
    old_DEM_votes = USA[state].dem_votes;
    old_REP_votes = USA[state].rep_votes;
    old_tp_votes = USA[state].third_votes;
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
        MC_second_case(old_DEM_votes, old_REP_votes, old_tp_votes,
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
void MC_second_case(int old_DEM_votes, int old_REP_votes, int old_TP_votes,
                    int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes, int procent) {
    int DEM_count = 0, REP_count = 0, TP_count = 0;
    // Reset the new votes for all parties
    *new_DEM_votes = 0;
    *new_REP_votes = 0;
    *new_TP_votes = 0;
    // DEM voters second preference
    for(int i = 0; i < old_DEM_votes; i++) {
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
    for(int i = 0; i < old_REP_votes; i++) {
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
    MC_first_case(old_TP_votes, new_DEM_votes, new_REP_votes, 2);
}
*/