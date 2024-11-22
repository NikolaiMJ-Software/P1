#include "../connecter.h"

char* PLPR(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0;
    int total_electors_us = 0;

        // Loop through all states
    for (int i = 0; i < STATES; i++) {
        int total_electors = USA[i].electors;  // Directly use electors from the state
        total_electors_us += total_electors;  // Add state's electors to the total
        int electors_dem = 0, electors_rep = 0, electors_tp = 0;

        // Use the provided votes for each party
        double dem_votes = USA[i].dem_votes;
        double rep_votes = USA[i].rep_votes;
        double tp_votes = USA[i].third_votes;

        // Allocate electors using Sainte-Laguë divisors

        int k_dem = 1, k_rep = 1, k_tp = 1; // Divisors start at 1
        while (total_electors > 0) {

            // Find the party with the highest quotient
            double dem_quotient = dem_votes / k_dem;
            double rep_quotient = rep_votes / k_rep;
            double tp_quotient = tp_votes / k_tp;

            if (dem_quotient >= rep_quotient && dem_quotient >= tp_quotient) {
                electors_dem++;
                k_dem += 2; //divisor Increase
            } else if (rep_quotient >= dem_quotient && rep_quotient >= tp_quotient) {
                electors_rep++;
                k_rep += 2; // divisor Increase
            } else {
                electors_tp++;
                k_tp += 2; // divisor Increase
            }

            total_electors--; // Decrement remaining electors
        }

        // Add state results to the national totals
        democrats += electors_dem;
        republicans += electors_rep;
        third_party += electors_tp;
    }

    // Print national results
    printf("Democrats: %d, Republicans: %d, Third Party: %d\n", democrats, republicans, third_party);

    // Return the winning party
    if (democrats > republicans && democrats > third_party) {
        return "Democrats";
    } else if (republicans > democrats && republicans > third_party) {
        return "Republicans";
    } else {
        return "Third Party";
    }
}
