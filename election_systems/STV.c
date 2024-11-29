#include "../connecter.h"
// a variable to define the amount of voter percentage that have an n+1 priority vote, when they have an n priority vote.
#define VOTE_DECREASE_RATIO 0.75

char* STV(states* USA, int* dem_electors, int* rep_electors, int* tp_electors) {
    int total_votes = 0, state_third_party_votes= 0, state_rep_party_votes = 0, state_dem_party_votes = 0,
        new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0,
        state_dem_electors = 0, state_rep_electors = 0, state_tp_electors = 0;
     *dem_electors = 0;
     *rep_electors = 0;
     *tp_electors = 0;


    for (int i = 0; i < STATES; i++) {
        //Firstly we initialize the votes from each state, so we can work with them.
        state_third_party_votes = USA[i].third_votes;
        state_rep_party_votes = USA[i].rep_votes;
        state_dem_party_votes = USA[i].dem_votes;
        total_votes = state_third_party_votes + state_rep_party_votes + state_dem_party_votes;
        //And define the required votes to be a percentage of votes based on the amount of electors.
        int required_votes = total_votes / USA[i].electors;
        //After this we give each party electors based on how many times they live up to the requirements.
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
        //After the electors are given, the party with the least amount of votes is eliminated, and their votes are given to the other parties based on their second priority.
        if ((state_third_party_votes <= state_rep_party_votes) && (state_third_party_votes <= state_dem_party_votes) && (state_third_party_votes != 0)) {
            USA[i].dem_votes *= VOTE_DECREASE_RATIO;
            USA[i].rep_votes *= VOTE_DECREASE_RATIO;
            USA[i].third_votes *= VOTE_DECREASE_RATIO;
            monte_carlo(USA, i, 1, &new_DEM_votes, &new_REP_votes, &new_TP_votes);
            state_third_party_votes = 0;
            state_dem_party_votes += new_DEM_votes;
            state_rep_party_votes += new_REP_votes;
        } else if ((state_dem_party_votes <= state_third_party_votes) && (state_dem_party_votes <= state_rep_party_votes) && (state_dem_party_votes != 0)) {
            USA[i].dem_votes *= VOTE_DECREASE_RATIO;
            USA[i].rep_votes *= VOTE_DECREASE_RATIO;
            USA[i].third_votes *= VOTE_DECREASE_RATIO;
            monte_carlo(USA, i, 1, &new_TP_votes, &new_REP_votes, &new_DEM_votes);
            state_third_party_votes += new_TP_votes;
            state_dem_party_votes = 0;
            state_rep_party_votes += new_REP_votes;
        } else if ((state_rep_party_votes <= state_third_party_votes) && (state_rep_party_votes <= state_dem_party_votes) && (state_rep_party_votes != 0)) {
            USA[i].dem_votes *= VOTE_DECREASE_RATIO;
            USA[i].rep_votes *= VOTE_DECREASE_RATIO;
            USA[i].third_votes *= VOTE_DECREASE_RATIO;
            monte_carlo(USA, i, 1, &new_DEM_votes, &new_TP_votes, &new_REP_votes);
            state_third_party_votes += new_TP_votes;
            state_dem_party_votes += new_DEM_votes;
            state_rep_party_votes = 0;
        }
        new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0;
        //This part helps if the amount of electors has yet to be reached, it then gives the party with the most votes an elector.
        while (1) {
            if (state_dem_electors + state_rep_electors + state_tp_electors < USA[i].electors) {
                if ((state_dem_party_votes > state_rep_party_votes) && (state_dem_party_votes > state_third_party_votes)) {
                    state_dem_electors++;
                    state_dem_party_votes = 0;
                } else if ((state_rep_party_votes > state_dem_party_votes) && (state_rep_party_votes > state_third_party_votes)) {
                    state_rep_electors++;
                    state_rep_party_votes = 0;
                } else if ((state_third_party_votes > state_dem_party_votes) && (state_third_party_votes > state_rep_party_votes)) {
                    state_tp_electors++;
                    state_third_party_votes = 0;
                }
            } else {
                break;
            }
        }
        //Printing of results, adding to overarching variable, and resetting of local variables.
        //printf("In the state %s, the electors were split: %d %d %d\n", USA[i].stateName, state_dem_electors, state_rep_electors, state_tp_electors);
        *dem_electors += state_dem_electors;
        *rep_electors += state_rep_electors;
        *tp_electors += state_tp_electors;
        state_dem_electors = 0, state_rep_electors = 0, state_tp_electors = 0;
    }
    // Print the electors for each party
    printf("\nDemocrat electors: %d\n", *dem_electors);
    printf("Republican electors: %d\n", *rep_electors);
    printf("Third party electors: %d\n", *tp_electors);
    printf("\nBecause the following party, got the biggest amount of electors, in regards to the Single Transferable Vote,\nthey are the winners.\nIf you are interested in learning more regarding Single Transferable Vote, you can read up on it on the following link: https://www.electoral-reform.org.uk/voting-systems/types-of-voting-system/single-transferable-vote/\n\n");

    //After every state has been gone through, compare overarching variables to find winner.
    if ((*dem_electors > *rep_electors) && (*dem_electors > *tp_electors)) {
        return "Democrats";
    } else if ((*rep_electors > *tp_electors) && (*rep_electors > *dem_electors)) {
        return "Republicans";
    } else if ((*tp_electors > *dem_electors) && (*tp_electors > *rep_electors)) {
        return "Third_party";
    } else {
        return "Tie";
    }
}