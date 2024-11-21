#include "../connecter.h"

char* STV(states* USA) {
    int democrats = 0, republicans = 0, third_party = 0;





    // Return winning party
    if (democrats > 270) {
        return "Democrats";
    } else if (republicans > 270){
        return "Republicans";
    } else {
        return "Third_party";
    }
}
