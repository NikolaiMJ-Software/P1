#include "connecter.h"
#include <stdio.h>

char* Winner_of_election(states* USA) {
    double democrats = 0, republicans = 0, third_party = 0;

    //count electors
    for (int i = 0; i < STATES; i++) {
        if (USA[i].democrats > USA[i].republicans) {
            democrats += USA[i].electors;
        } else {
            republicans += USA[i].electors;
        }
    }
    //

    //return winner;
}