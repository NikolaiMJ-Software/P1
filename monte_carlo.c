#include "connecter.h"
#include <time.h>
#define comparisons 50000

// Monte Carlo study
void monte_carlo(states* USA, int choice) {
    // restart rand
    srand(time(NULL));

    int D_count = 0, R_count = 0, TP_count = 0, new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0, TOT_DEM_votes = 0, TOT_REP_votes = 0, TOT_tp_votes = 0;
    // calculate the total of the votes, from different parties
    for (int i = 0; i < STATES; i++) {
        TOT_tp_votes += USA[i].third_votes;
    }
    for (int i = 0; i < STATES; i++) {
        TOT_DEM_votes += USA[i].dem_votes;
    }
    for (int i = 0; i < STATES; i++) {
        TOT_REP_votes += USA[i].rep_votes;
    }

    // CASE 1: if the third-party votes get lost, and have to chose between DEM og REP
    for(int i = 0; i < TOT_tp_votes; i++) {
        for(int j = 0; j < comparisons; j++) {
            int r_no = 0;
            r_no = rand() % 2;
            if (r_no) {
                D_count++;
            } else {
                R_count++;
            }
        }
        if (D_count < R_count) {
            new_REP_votes++;
        } else {
            new_DEM_votes++;
        }
    }
    // return TP secund choice

    // CASE 2: All voters second preference
    D_count = 0, R_count = 0, TP_count = 0, new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0;
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
    //return new votes

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
    // return new votes

    // Run CASE 2 again
}