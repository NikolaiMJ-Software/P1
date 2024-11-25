#include "../connecter.h"

char* STV(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0;



    // Call Monte Carlo
    // Creat new results
    int new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0;
    // Call function, "1" for "case 1" (ONLY third party second preference) and "2" for "case 2" (All second preference)
    //monte_carlo(USA, 1, &new_DEM_votes, &new_REP_votes, &new_TP_votes);
    // Print return values from Monte Carlo
    printf("New DEM votes: %d\n", new_DEM_votes);
    printf("New REP votes: %d\n", new_REP_votes);
    printf("New TP votes: %d\n", new_TP_votes);

    // Return winning party
    if (democrats > 270) {
        return "Democrats";
    } else if (republicans > 270){
        return "Republicans";
    } else {
        return "Third_party";
    }
}
