#include "connecter.h"
#include <stdio.h>

char* Winner_of_election(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0;

    //Count electors, from the percent of votes
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