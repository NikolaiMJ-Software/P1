#include "../connecter.h"

char* electoral_college(states* USA, int year) {
    int democrats = 0, republicans = 0, third_party = 0, electors = 0;
    // Distribute the electors based on the highest percentage in the state
    for (int i = 0; i < STATES; i++) {
        electors += USA[i].electors;
        if (USA[i].democrats > USA[i].third_party  && USA[i].democrats > USA[i].republicans) {
            if (strcmp(USA[i].stateName,"Maine") == 0 && year == 2016) {
                democrats += USA[i].electors;
                democrats--;
                republicans++;
            } else {
                democrats += USA[i].electors;
            }
        } else if (USA[i].republicans > USA[i].third_party) {
            republicans += USA[i].electors;
        } else {
            third_party += USA[i].electors;
        }

    }
    // Print the electors for each party
    printf("\nDemocrat electors: %d\n", democrats);
    printf("Republican electors: %d\n", republicans);
    printf("Third party electors: %d\n\n", third_party);
    // Return winning party
    if (democrats > (electors/2)+1) {
        return "Democrats";
    } else if (republicans > (electors/2)+1){
        return "Republicans";
    } else {
        return "Third_party";
    }
}