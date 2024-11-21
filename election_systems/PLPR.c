#include "../connecter.h"


char* PLPR(states* USA){
    int democrats = 0, republicans = 0, third_party = 0;

// note population needs to be fixed other than that should work.
    for (int i = 0; i < STATES; i++) {
        int total_electors = USA[i].population / 1000000; // 1000000 er en divisor for at opdele populationen proportionelt
        int electors_dem = 0, electors_rep = 0, electors_tp = 0;

        // Initial vote totals for the state
        double dem_votes = USA[i].population * (USA[i].democrats / 100.0);
        double rep_votes = USA[i].population * (USA[i].republicans / 100.0);
        double tp_votes = USA[i].population * ((100.0 - USA[i].democrats - USA[i].republicans) / 100.0);

        // Allocate electors using Sainte-Laguë divisors
        for (int k = 1; total_electors > 0; k += 2) {
            if (dem_votes >= rep_votes && dem_votes >= tp_votes) {
                electors_dem++;
                dem_votes /= (k + 2);
            } else if (rep_votes >= dem_votes && rep_votes >= tp_votes) {
                electors_rep++;
                rep_votes /= (k + 2);
            } else {
                electors_tp++;
                tp_votes /= (k + 2);
            }
            total_electors--;
        }

        // Add state results to the national totals
        democrats += electors_dem;
        republicans += electors_rep;
        third_party += electors_tp;
    }

    printf("Democrats: %d, Republicans: %d, Third Party: %d\n", democrats, republicans, third_party);


    // Return winning party
    if (democrats > republicans && democrats > third_party) {
        return "Democrats";
    } else if (republicans > democrats && republicans > third_party) {
        return "Republicans";
    } else {
        return "Third Party";
    }

}
