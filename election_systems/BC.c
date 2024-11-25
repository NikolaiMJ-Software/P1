#include "../connecter.h"

char* BC(states* USA) {
    int total_votes = 0, state_third_party_votes= 0, state_rep_party_votes = 0, state_dem_party_votes = 0;
    int new_DEM_votes_2nd = 0, new_REP_votes_2nd = 0, new_TP_votes_2nd = 0;
    double dem_points = 0, rep_points = 0, tp_points = 0;
    int new_DEM_votes_3nd = 0, new_REP_votes_3nd = 0, new_TP_votes_3nd = 0;
    int dem_electors = 0, rep_electors = 0, tp_electors = 0;
    for (int i = 0; i<STATES; i++) {
        total_votes = USA[i].dem_votes+USA[i].rep_votes+USA[i].third_votes;

        state_third_party_votes = USA[i].third_votes;
        state_rep_party_votes = USA[i].rep_votes;
        state_dem_party_votes = USA[i].dem_votes;

        monte_carlo(state_dem_party_votes, state_rep_party_votes, state_third_party_votes, 2, &new_DEM_votes_2nd, &new_REP_votes_2nd, &new_TP_votes_2nd);

        printf("%d\n", new_DEM_votes_2nd);
        printf("%d\n", new_REP_votes_2nd);
        printf("%d\n", new_TP_votes_2nd);

        new_DEM_votes_3nd = total_votes - new_DEM_votes_2nd-USA[i].dem_votes;
        new_REP_votes_3nd = total_votes - new_REP_votes_2nd-USA[i].rep_votes;
        new_TP_votes_3nd =  total_votes - new_TP_votes_2nd-USA[i].third_votes;

        dem_points = USA[i].dem_votes+(0.5*new_DEM_votes_2nd)+(0.33*new_DEM_votes_3nd);
        rep_points = USA[i].rep_votes+(0.5*new_REP_votes_2nd)+(0.33*new_REP_votes_3nd);
        tp_points = USA[i].third_votes+(0.5*new_TP_votes_2nd)+(0.33*new_TP_votes_3nd);

        //printf("State: %s: \n", USA[i].stateName);
        //printf("Democrat points: %0.2lf \n", dem_points);
        //printf("Rep points: %0.2lf \n", rep_points);
        //printf("TP points: %0.2lf \n\n", tp_points);

        if(dem_points>rep_points && dem_points>tp_points) {
            dem_electors += USA[i].electors;
        } else if(rep_points>dem_points && rep_points>tp_points) {
            rep_electors += USA[i].electors;
        } else if(tp_points>dem_points && tp_points>rep_points) {
            tp_electors += USA[i].electors;
        }
    }
    // Call function Monte Carlo to define second choice
    //define third choice

    printf("democrat electors: %d \n",dem_electors);
    printf("republican electors: %d \n",rep_electors);
    printf("third party electors: %d \n",tp_electors);

    // Return winning party
    if (dem_electors > rep_electors && dem_electors > tp_electors) {
        return "Democrats";
    } else if (rep_electors > dem_electors && rep_electors > tp_electors) {
        return "Republicans";
    } else {
        return "Third Party";
    }
}
