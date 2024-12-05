#include "../connecter.h"

char* BC(states* USA, cmp* e_systems, cmp* uncap_systems, int activate_progress, int counter_cap, int counter_uncap, int uncapped, int states_abolished) {
    int total_electors = 0, allocated_dem_electors = 0, allocated_rep_electors = 0, allocated_tp_electors = 0,
        percentage = -2;
    double dem_points_sum = 0, rep_points_sum = 0, tp_points_sum = 0;

    // Arrays to store fractional values and remaining electors
    double dem_fraction[STATES], rep_fraction[STATES], tp_fraction[STATES];

    for (int i = 0; i < STATES; i++) {
        int total_votes = USA[i].dem_votes + USA[i].rep_votes + USA[i].third_votes;

        // Monte Carlo simulation: second-choice votes
        int new_DEM_votes_2nd, new_REP_votes_2nd, new_TP_votes_2nd;
        monte_carlo(USA, i, 0, &new_DEM_votes_2nd, &new_REP_votes_2nd, &new_TP_votes_2nd);

        int new_DEM_votes_3rd = total_votes - new_DEM_votes_2nd - USA[i].dem_votes;
        int new_REP_votes_3rd = total_votes - new_REP_votes_2nd - USA[i].rep_votes;
        int new_TP_votes_3rd = total_votes - new_TP_votes_2nd - USA[i].third_votes;

        // Calculate points based on Nauru BC
        double dem_points = USA[i].dem_votes + (0.5 * new_DEM_votes_2nd) + (0.33 * new_DEM_votes_3rd);
        double rep_points = USA[i].rep_votes + (0.5 * new_REP_votes_2nd) + (0.33 * new_REP_votes_3rd);
        double tp_points = USA[i].third_votes + (0.5 * new_TP_votes_2nd) + (0.33 * new_TP_votes_3rd);
        double total_points = dem_points + rep_points + tp_points;

        // Calculate proportional allocation
        dem_fraction[i] = (USA[i].electors * (dem_points / total_points));
        rep_fraction[i] = (USA[i].electors * (rep_points / total_points));
        tp_fraction[i] = (USA[i].electors * (tp_points / total_points));

        // Allocate electors
        allocated_dem_electors += (int)dem_fraction[i];
        allocated_rep_electors += (int)rep_fraction[i];
        allocated_tp_electors += (int)tp_fraction[i];

        // Accumulate fractional sums
        dem_points_sum += dem_fraction[i] - (int)dem_fraction[i];
        rep_points_sum += rep_fraction[i] - (int)rep_fraction[i];
        tp_points_sum += tp_fraction[i] - (int)tp_fraction[i];

        total_electors += USA[i].electors;

        if (activate_progress) {
            // Print the percentage complete
            percentage = percentage + 2;
            printf("Progress: %d%%\n", percentage);
        }
    }
    printf("\n");

    // Adjust missing electors using largest remainder method
    int missing_electors = total_electors - (allocated_dem_electors + allocated_rep_electors + allocated_tp_electors);
    while (missing_electors > 0) {
        if (dem_points_sum > rep_points_sum && dem_points_sum > tp_points_sum) {
            (allocated_dem_electors)++;
            dem_points_sum -= 1;
        } else if (rep_points_sum > tp_points_sum && rep_points_sum > dem_points_sum) {
            (allocated_rep_electors)++;
            rep_points_sum -= 1;
        } else {
            (allocated_tp_electors)++;
            tp_points_sum -= 1;
        }
        missing_electors--;
    }

    // Print results
    printf("\nDemocrat electors: %d\n", allocated_dem_electors);
    printf("Republican electors: %d\n", allocated_rep_electors);
    printf("Third party electors: %d\n", allocated_tp_electors);
    printf("\nBecause the following party, got the biggest amount of points, in regards to the Nauru Borda Count system,\nthey are the winners.\nIf you are interested in learning more regarding Nauru Borda Count, you can read up on it on the following link: \nhttps://crawford.anu.edu.au/pdf/staff/ben_reilly/ReillyB_05.pdf\n\n");
    // Save the electors in the cmp systems array
    if (!states_abolished) {
    } else if (uncapped) {
        strcpy(uncap_systems[counter_uncap].system_name, "BC");
        uncap_systems[counter_uncap].DEM_electors = allocated_dem_electors;
        uncap_systems[counter_uncap].REP_electors = allocated_rep_electors;
        uncap_systems[counter_uncap].TP_electors = allocated_tp_electors;
    } else {
        strcpy(e_systems[counter_cap].system_name, "BC");
        e_systems[counter_cap].DEM_electors = allocated_dem_electors;
        e_systems[counter_cap].REP_electors = allocated_rep_electors;
        e_systems[counter_cap].TP_electors = allocated_tp_electors;
    }

    // Determine winner
    if (allocated_dem_electors > allocated_rep_electors && allocated_dem_electors > allocated_tp_electors) {
        return "Democrats";
    } else if (allocated_rep_electors > allocated_dem_electors && allocated_rep_electors > allocated_tp_electors) {
        return "Republicans";
    } else if(allocated_tp_electors > allocated_dem_electors && allocated_tp_electors > allocated_rep_electors) {
        return "Third Party";
    } else {
        return "Tie";
    }
}