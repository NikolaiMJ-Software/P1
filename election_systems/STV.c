#include "../connecter.h"
// A variable to define the amount of voter percentage that have an n+1 priority vote, when they have an n priority vote.
#define VOTE_DECREASE_RATIO 0.75

// Simulate the Single Transferable Vote from Australia
char* STV(states* USA, cmp* cap_systems, cmp* uncap_systems, int activate_progress, int counter_cap, int counter_uncap, int uncapped, int states_abolished) {
    int total_votes = 0, state_third_party_votes= 0, state_rep_party_votes = 0, state_dem_party_votes = 0,
        new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0,
        state_dem_electors = 0, state_rep_electors = 0, state_tp_electors = 0,
        percentage = -2,
        dem_electors = 0, rep_electors = 0, tp_electors = 0;

    // Print a wait message to the user when the states is abolished
    if (states_abolished) {
        printf("\nPlease wait...");
    } else {
        printf("\n");
    }
    for (int i = 0; i < STATES; i++) {
        // Firstly we initialize the votes from each state, so we can work with them.
        state_third_party_votes = USA[i].third_votes;
        state_rep_party_votes = USA[i].rep_votes;
        state_dem_party_votes = USA[i].dem_votes;
        total_votes = state_third_party_votes + state_rep_party_votes + state_dem_party_votes;
        // And define the required votes to be a percentage of votes based on the amount of electors.
        int required_votes = total_votes / USA[i].electors;
        // After this we give each party electors based on how many times they live up to the requirements.
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
        // After the electors are given, the party with the least amount of votes is eliminated, and their votes are given to the other parties based on their second priority.
        if ((state_third_party_votes <= state_rep_party_votes) && (state_third_party_votes <= state_dem_party_votes) && (state_third_party_votes != 0)) {
            // Third party second preference
            USA[i].dem_votes = state_dem_party_votes * VOTE_DECREASE_RATIO;
            USA[i].rep_votes = state_rep_party_votes * VOTE_DECREASE_RATIO;
            USA[i].third_votes = state_third_party_votes * VOTE_DECREASE_RATIO;
            monte_carlo(USA, i, 3, &new_DEM_votes, &new_REP_votes, &new_TP_votes);
            state_third_party_votes = 0;
            state_dem_party_votes += new_DEM_votes;
            state_rep_party_votes += new_REP_votes;
        } else if ((state_dem_party_votes <= state_third_party_votes) && (state_dem_party_votes <= state_rep_party_votes) && (state_dem_party_votes != 0)) {
            // DEM second preference
            USA[i].dem_votes = state_dem_party_votes * VOTE_DECREASE_RATIO;
            USA[i].rep_votes = state_rep_party_votes * VOTE_DECREASE_RATIO;
            USA[i].third_votes = state_third_party_votes * VOTE_DECREASE_RATIO;
            monte_carlo(USA, i, 1, &new_DEM_votes, &new_REP_votes, &new_TP_votes);
            state_third_party_votes += new_TP_votes;
            state_dem_party_votes = 0;
            state_rep_party_votes += new_REP_votes;
        } else if ((state_rep_party_votes <= state_third_party_votes) && (state_rep_party_votes <= state_dem_party_votes) && (state_rep_party_votes != 0)) {
            // REP second preference
            USA[i].dem_votes = state_dem_party_votes * VOTE_DECREASE_RATIO;
            USA[i].rep_votes = state_rep_party_votes * VOTE_DECREASE_RATIO;
            USA[i].third_votes = state_third_party_votes * VOTE_DECREASE_RATIO;
            monte_carlo(USA, i, 2, &new_DEM_votes, &new_REP_votes, &new_TP_votes);
            state_third_party_votes += new_TP_votes;
            state_dem_party_votes += new_DEM_votes;
            state_rep_party_votes = 0;
        }
        new_DEM_votes = 0, new_REP_votes = 0, new_TP_votes = 0;
        // This part helps if the amount of electors has yet to be reached, it then gives the party with the most votes an elector.
        while (1) {
            if (state_dem_electors + state_rep_electors + state_tp_electors < USA[i].electors) {
                if ((state_dem_party_votes > state_rep_party_votes) && (state_dem_party_votes > state_third_party_votes)) {
                    state_dem_electors++;
                    state_dem_party_votes -= required_votes;
                } else if ((state_rep_party_votes > state_dem_party_votes) && (state_rep_party_votes > state_third_party_votes)) {
                    state_rep_electors++;
                    state_rep_party_votes -= required_votes;
                } else if ((state_third_party_votes > state_dem_party_votes) && (state_third_party_votes > state_rep_party_votes)) {
                    state_tp_electors++;
                    state_third_party_votes -= required_votes;
                }
            } else {
                break;
            }
        }
        dem_electors += state_dem_electors;
        rep_electors += state_rep_electors;
        tp_electors += state_tp_electors;
        state_dem_electors = 0, state_rep_electors = 0, state_tp_electors = 0;

        if (activate_progress && !states_abolished) {
            // Print the percentage complete
            percentage = percentage + 2;
            printf("\rProgress: %d%%", percentage);
        }
        if (states_abolished == 1) {
            break;
        }
    }
    // Print the electors for each party
    printf("\n\nDemocrat electors: %d\n", dem_electors);
    printf("Republican electors: %d\n", rep_electors);
    printf("Third party electors: %d\n\n", tp_electors);
    // Save the electors in the cmp systems array
    if (!states_abolished) {
        if (uncapped) {
            strcpy(uncap_systems[counter_uncap].system_name, "STV");
            uncap_systems[counter_uncap].DEM_electors = dem_electors;
            uncap_systems[counter_uncap].REP_electors = rep_electors;
            uncap_systems[counter_uncap].TP_electors = tp_electors;
        } else {
            strcpy(cap_systems[counter_cap].system_name, "STV");
            cap_systems[counter_cap].DEM_electors = dem_electors;
            cap_systems[counter_cap].REP_electors = rep_electors;
            cap_systems[counter_cap].TP_electors = tp_electors;
        }
        // Copy system names from cap to uncap, and opposite
        copy_systems_names(cap_systems, uncap_systems);
    }
    // After every state has been gone through, compare overarching variables to find winner.
    if ((dem_electors > rep_electors) && (dem_electors > tp_electors)) {
        return "Democrats";
    } else if ((rep_electors > tp_electors) && (rep_electors > dem_electors)) {
        return "Republicans";
    } else if ((tp_electors > dem_electors) && (tp_electors > rep_electors)) {
        return "Third_party";
    } else {
        return "Tie";
    }
}