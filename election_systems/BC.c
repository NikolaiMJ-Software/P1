#include "../connecter.h"

char* BC(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0;

    int new_DEM_votes_2nd = 0, new_REP_votes_2nd = 0, new_TP_votes_2nd = 0;
    int new_DEM_votes_3nd = 0, new_REP_votes_3nd = 0, new_TP_votes_3nd = 0;
    // Call function, "1" for "case 1" (ONLY third party second preference) and "2" for "case 2" (All second preference)
    monte_carlo(USA, 2, &new_DEM_votes_2nd, &new_REP_votes_2nd, &new_TP_votes_2nd);
    monte_carlo(USA, 2, &new_DEM_votes_3nd, &new_REP_votes_3nd, &new_TP_votes_3nd);
    // Print return values from Monte Carlo
    printf("New DEM votes: %d\n", new_DEM_votes_2nd);
    printf("New REP votes: %d\n", new_REP_votes_2nd);
    printf("New TP votes: %d\n", new_TP_votes_2nd);

    printf("New DEM votes: %d\n", new_DEM_votes_3nd);
    printf("New REP votes: %d\n", new_REP_votes_3nd);
    printf("New TP votes: %d\n", new_TP_votes_3nd);

    // Return winning party

}
