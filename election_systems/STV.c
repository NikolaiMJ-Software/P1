#include "../connecter.h"
#include <math.h>
#define VOTE_DECREASE_RATIO 0.75

char* STV(states* USA) {
    int total_votes = 0, state_third_party_votes= 0, state_rep_party_votes = 0, state_dem_party_votes = 0,
        new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0,
        state_dem_electors = 0, state_rep_electors = 0, state_tp_electors = 0,
        dem_electors = 0, rep_electors = 0, tp_electors = 0;
    for (int i = 0; i < STATES; i++) {
        state_third_party_votes = USA[i].third_votes;
        state_rep_party_votes = USA[i].rep_votes;
        state_dem_party_votes = USA[i].dem_votes;
        total_votes = state_third_party_votes + state_rep_party_votes + state_dem_party_votes;
        int required_votes = total_votes / USA[i].electors;
        for (int j = 0; j < 3; j++) {
            while (state_third_party_votes >= required_votes || state_rep_party_votes >= required_votes || state_dem_party_votes >= required_votes) {
                if (state_third_party_votes >= required_votes) {
                    state_tp_electors++;
                    state_third_party_votes -= required_votes;
                }
                if (state_rep_party_votes >= required_votes) {
                    state_rep_electors++;
                    state_rep_party_votes -= required_votes;
                }
                if (state_dem_party_votes >= required_votes) {
                    state_dem_electors++;
                    state_dem_party_votes -= required_votes;
                }
            }
            if ((state_third_party_votes <= state_rep_party_votes) && (state_third_party_votes <= state_dem_party_votes) && (state_third_party_votes != 0)) {
                monte_carlo(state_dem_party_votes * VOTE_DECREASE_RATIO, state_rep_party_votes * VOTE_DECREASE_RATIO, state_third_party_votes * VOTE_DECREASE_RATIO, 1, &new_DEM_votes, &new_REP_votes, &new_TP_votes);
                state_third_party_votes = 0;
                state_dem_party_votes += new_DEM_votes;
                state_rep_party_votes += new_REP_votes;
            } else if ((state_dem_party_votes <= state_third_party_votes) && (state_dem_party_votes <= state_rep_party_votes) && (state_dem_party_votes != 0)) {
                monte_carlo(state_third_party_votes * VOTE_DECREASE_RATIO, state_rep_party_votes * VOTE_DECREASE_RATIO, state_dem_party_votes * VOTE_DECREASE_RATIO, 1, &new_TP_votes, &new_REP_votes, &new_DEM_votes);
                state_third_party_votes += new_TP_votes;
                state_dem_party_votes = 0;
                state_rep_party_votes += new_REP_votes;
            } else if ((state_rep_party_votes <= state_third_party_votes) && (state_rep_party_votes <= state_dem_party_votes) && (state_rep_party_votes != 0)) {
                monte_carlo(state_dem_party_votes * VOTE_DECREASE_RATIO, state_third_party_votes * VOTE_DECREASE_RATIO, state_rep_party_votes * VOTE_DECREASE_RATIO, 1, &new_DEM_votes, &new_TP_votes, &new_REP_votes);
                state_third_party_votes += new_TP_votes;
                state_dem_party_votes += new_DEM_votes;
                state_rep_party_votes = 0;
            }
            new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0;
        }
        printf("In the state %s, the electors were split: %d %d %d", USA[i].stateName, state_dem_electors, state_rep_electors, state_tp_electors);
        dem_electors += state_dem_electors;
        rep_electors += state_rep_electors;
        tp_electors += state_tp_electors;
    }
    if (dem_electors > 270) {
        return "Democrats";
    } else if (rep_electors > 270){
        return "Republicans";
    } else if (tp_electors > 270){
        return "Third_party";
    } else {
        return "No_Winner";
    }
}