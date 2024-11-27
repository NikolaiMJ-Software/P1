#include "connecter.h"
int proportionality, minority_representation, party_system_concentration, personalization, legitimacy, comprehensibility;
states comprehensibility_function(states state, int comprehensibility);
states minority_and_proportionality_function(states state, int minority_proportionality);
states personalization_function(states state, int personalization);
states legitimacy_function(states state, int legitimacy);
states parameters(states state, int minority_proportionality, int personalization, int legitimacy, int comprehensibility) {
    state = comprehensibility_function(state, comprehensibility);
    state = minority_and_proportionality_function(state, minority_proportionality);
    state = personalization_function(state, personalization);
    state = legitimacy_function(state, legitimacy);
    return state;
}
states comprehensibility_function(states state, int comprehensibility) {
    return state;
}
states minority_and_proportionality_function(states state, int minority_proportionality) {
    return state;
}
states personalization_function(states state, int personalization) {
    return state;
}
states legitimacy_function(states state, int legitimacy) {
    return state;
}