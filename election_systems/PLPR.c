#include "../connecter.h"

//simulate the party list proportional representation system from Norway (PLPR)
char* PLPR(states* USA, cmp* cap_systems, cmp* uncap_systems, int counter_cap, int counter_uncap, int uncapped, int states_abolished) {
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
    // Print the electors for each party
    printf("\nDemocrat electors: %d\n", democrats);
    printf("Republican electors: %d\n", republicans);
    printf("Third party electors: %d\n", third_party);
    printf("\nBecause the following party got the biggest amount of electors, in regards to the \nParty List Proportional Representation, they are the winners.\nIf you are interested in learning more regarding Party List Proportional Representation, \nyou can read up on it on the following link: \nhttps://www.electoral-reform.org.uk/voting-systems/types-of-voting-system/party-list-pr/\n\n");
    // Save the electors in the cmp systems array
    if (!states_abolished) {
        if (uncapped) {
            strcpy(uncap_systems[counter_uncap].system_name, "PLPR");
            uncap_systems[counter_uncap].DEM_electors = democrats;
            uncap_systems[counter_uncap].REP_electors = republicans;
            uncap_systems[counter_uncap].TP_electors = third_party;
        } else {
            strcpy(cap_systems[counter_cap].system_name, "PLPR");
            cap_systems[counter_cap].DEM_electors = democrats;
            cap_systems[counter_cap].REP_electors = republicans;
            cap_systems[counter_cap].TP_electors = third_party;
        }
    }
    // Return the winning party
    if (democrats > republicans && democrats > third_party) {
        return "Democrats";
    } else if (republicans > democrats && republicans > third_party) {
        return "Republicans";
    } else if (third_party > democrats && third_party > republicans) {
        return "Third Party";
    } else {
        return "Tie";
    }

}
