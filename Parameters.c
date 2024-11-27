#include "connecter.h"
states comprehensibility_function(states state, int comprehensibility);
states minority_and_proportionality_function(states state, double minority_proportionality);
states personalization_function(states state, int personalization);
states legitimacy_function(states state, int legitimacy);
states parameters(states state, double minority_proportionality, int personalization, int legitimacy, int comprehensibility) {
    state = comprehensibility_function(state, comprehensibility);
    state = minority_and_proportionality_function(state, minority_proportionality);
    state = personalization_function(state, personalization);
    state = legitimacy_function(state, legitimacy);
    return state;
}
states comprehensibility_function(states state, int comprehensibility) {
    return state;
}
states minority_and_proportionality_function(states state, double minority_proportionality) {
    if (state.dem_votes > state.rep_votes && state.dem_votes > state.third_votes) {
        state.dem_votes = state.dem_votes + state.rep_votes + state.third_votes - (state.rep_votes + state.third_votes) * minority_proportionality / 100;
        state.rep_votes *= minority_proportionality / 100;
        state.third_votes *= minority_proportionality / 100;
    } else if (state.rep_votes > state.dem_votes && state.rep_votes > state.third_votes) {
        state.rep_votes = state.dem_votes + state.rep_votes + state.third_votes - (state.dem_votes + state.third_votes) * minority_proportionality / 100;
        state.dem_votes *= minority_proportionality / 100;
        state.third_votes *= minority_proportionality / 100;
    } else if (state.third_votes > state.dem_votes && state.third_votes > state.rep_votes) {
        state.third_votes = state.dem_votes + state.rep_votes + state.third_votes - (state.rep_votes + state.dem_votes) * minority_proportionality / 100;
        state.rep_votes *= minority_proportionality / 100;
        state.dem_votes *= minority_proportionality / 100;
    }
    return state;
}
states personalization_function(states state, int personalization) {
    return state;
}
states legitimacy_function(states state, int legitimacy) {
    return state;
}