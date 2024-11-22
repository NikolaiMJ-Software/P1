#include "connecter.h"
#include <time.h>
#define comparisons 50000

void MC_first_case(int TOT_tp_votes, int* new_DEM_votes, int* new_REP_votes);
void MC_second_case(int TOT_DEM_votes, int TOT_REP_votes, int TOT_TP_votes);

// Monte Carlo study
void monte_carlo(states* USA, int choice) {
    // restart rand
    srand(time(NULL));

    int TOT_DEM_votes = 0, TOT_REP_votes = 0, TOT_TP_votes = 0,
        new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0;
    // calculate the total of the votes, from different parties
    for (int i = 0; i < STATES; i++) {
        TOT_TP_votes += USA[i].third_votes;
        TOT_DEM_votes += USA[i].dem_votes;
        TOT_REP_votes += USA[i].rep_votes;
    }

    if (choice == 1) {
        MC_first_case(TOT_TP_votes, &new_DEM_votes, &new_REP_votes);
        // return result
    } else if (choice == 2) {
        MC_second_case(TOT_DEM_votes, TOT_REP_votes, TOT_TP_votes);
        // return result
    }
    // TEST print return values
    printf("New DEM votes: %d\n", new_DEM_votes);
    printf("New REP votes: %d\n", new_REP_votes);
    printf("New TP votes: %d\n", new_TP_votes);
}

void MC_first_case(int TOT_tp_votes, int* new_DEM_votes, int* new_REP_votes) {
    // CASE 1: if the third-party votes get lost, and have to chose between DEM og REP
    int DEM_count = 0, REP_count = 0;
    *new_DEM_votes = 0;
    *new_REP_votes = 0;
    for(int i = 0; i < TOT_tp_votes; i++) {
        for(int j = 0; j < comparisons; j++) {
            int r_no = 0;
            r_no = rand() % 2;
            if (r_no) {
                DEM_count++;
            } else {
                REP_count++;
            }
        }
        if (DEM_count < REP_count) {
            *new_REP_votes++;
        } else {
            *new_DEM_votes++;
        }
        DEM_count = 0;
        REP_count = 0;
    }
    // return TP secund choice
}

void MC_second_case(int TOT_DEM_votes, int TOT_REP_votes, int TOT_TP_votes) {
    // CASE 2: All voters second preference
    int D_count = 0, R_count = 0, TP_count = 0, new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0;
    // DEM
    for(int i = 0; i < TOT_DEM_votes; i++) {
        for(int j = 0; j < comparisons; j++) {
            int r_no = 0;
            r_no = rand() % 3;
            if (r_no < 3) {
                TP_count++;
            } else {
                R_count++;
            }
        }
        if (TP_count < R_count) {
            new_REP_votes++;
        } else {
            new_TP_votes++;
        }
    }

    D_count = 0, TP_count = 0;
    // REP
    for(int i = 0; i < TOT_REP_votes; i++) {
        for(int j = 0; j < comparisons; j++) {
            int r_no = 0;
            r_no = rand() % 3;
            if (r_no < 3) {
                TP_count++;
            } else {
                D_count++;
            }
        }
        if (TP_count < D_count) {
            new_DEM_votes++;
        } else {
            new_TP_votes++;
        }
    }

    MC_first_case(TOT_TP_votes);

    // return teh new votes
}