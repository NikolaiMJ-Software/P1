#include "connecter.h"

char* electoral_college(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0;
    // destructure the electors based on the highest percentage in the sate
    for (int i = 0; i < STATES; i++) {
        if (USA[i].democrats > USA[i].republicans) {
            democrats += USA[i].electors;
        } else {
            republicans += USA[i].electors;
        }
    }
    // Return winning party
    if (democrats > republicans) {
        return "Democrats";
    } else {
        return "Republicans";
    }
}