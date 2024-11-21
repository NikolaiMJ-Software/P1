#include "../connecter.h"

char* electoral_college(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0;
    // Distribute the electors based on the highest percentage in the state
    for (int i = 0; i < STATES; i++) {
        double third_p = 100 - USA[i].democrats - USA[i].republicans;
        if (USA[i].democrats > third_p && USA[i].democrats > USA[i].republicans) {
            democrats += USA[i].electors;
        } else if (USA[i].republicans > third_p) {
            republicans += USA[i].electors;
        } else {
            third_party += USA[i].electors;
        }
    }
    // Return winning party
    if (democrats > 270) {
        return "Democrats";
    } else if (republicans > 270){
        return "Republicans";
    } else {
        return "Third_party";
    }
}