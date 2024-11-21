#include "../connecter.h"


char* PLPR(states* USA){
    int democrats = 0, republicans = 0, third_party = 0;

for (int i = 0; i < STATES; i++) {




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
