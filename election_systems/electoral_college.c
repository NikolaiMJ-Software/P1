#include "../connecter.h"

char* electoral_college(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0, electors = 0;
    // Distribute the electors based on the highest percentage in the state
    for (int i = 0; i < STATES; i++) {
        electors += USA[i].electors;
        double third_p = 100 - USA[i].democrats - USA[i].republicans;
        if (USA[i].democrats > third_p && USA[i].democrats > USA[i].republicans) {
            democrats += USA[i].electors;
        } else if (USA[i].republicans > third_p) {
            republicans += USA[i].electors;
        } else {
            third_party += USA[i].electors;
        }
    }
    printf("democrat electors: %d\n", democrats);
    printf("republican electors: %d\n", republicans);
    printf("third party electors: %d\n", third_party);
    // Return winning party
    if (democrats > (electors/2)+1) {
        return "Democrats";
    } else if (republicans > (electors/2)+1){
        return "Republicans";
    } else {
        return "Third_party";
    }
}