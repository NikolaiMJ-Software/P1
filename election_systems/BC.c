#include "../connecter.h"

char* BC(states* USA) {
    int total_votes = 0, total_votes_dem = 0, total_votes_rep = 0, total_votes_third = 0;
    for (int i = 0; i<STATES; i++) {
        total_votes += USA[i].dem_votes+USA[i].rep_votes+USA[i].third_votes;
        total_votes_dem += USA[i].dem_votes;
        total_votes_rep += USA[i].rep_votes;
        total_votes_third += USA[i].third_votes;
    }
    double dem_points = 0, rep_points = 0, tp_points = 0;
    // Call function Monte Carlo to define second choice
    int new_DEM_votes_2nd = 0, new_REP_votes_2nd = 0, new_TP_votes_2nd = 0;
    monte_carlo(USA, 2, &new_DEM_votes_2nd, &new_REP_votes_2nd, &new_TP_votes_2nd);
    //define third choice
    int new_DEM_votes_3nd = 0, new_REP_votes_3nd = 0, new_TP_votes_3nd = 0;
    new_DEM_votes_3nd = total_votes - new_DEM_votes_2nd-total_votes_dem;
    new_REP_votes_3nd = total_votes - new_REP_votes_2nd-total_votes_rep;
    new_TP_votes_3nd =  total_votes - new_TP_votes_2nd-total_votes_third;

    // Print return values from Monte Carlo
    printf("New DEM votes: %d\n", new_DEM_votes_2nd);
    printf("New REP votes: %d\n", new_REP_votes_2nd);
    printf("New TP votes: %d\n", new_TP_votes_2nd);

    printf("New DEM votes: %d\n", new_DEM_votes_3nd);
    printf("New REP votes: %d\n", new_REP_votes_3nd);
    printf("New TP votes: %d\n", new_TP_votes_3nd);

    //Calculate the amount of points from the different votes
    for (int i = 0; i < STATES; i++) {
        dem_points = USA[i].dem_votes+(0.5*new_DEM_votes_2nd)+(0.33*new_DEM_votes_3nd);
        rep_points = USA[i].rep_votes+(0.5*new_REP_votes_2nd)+(0.33*new_REP_votes_3nd);
        tp_points = USA[i].third_votes+(0.5*new_TP_votes_2nd)+(0.33*new_TP_votes_3nd);
    }
    printf("DEM points: %lf\n", dem_points);
    printf("REP points: %lf\n", rep_points);
    printf("TP points: %lf\n", tp_points);
    printf("Total votes: %d\n", total_votes);
    printf("Total votes_dem: %d\n", total_votes_dem+new_DEM_votes_2nd+new_DEM_votes_3nd);
    printf("Total votes_rep: %d\n", total_votes_rep+new_REP_votes_2nd+new_REP_votes_3nd);
    printf("Total votes_third: %d\n", total_votes_third+new_TP_votes_2nd+new_TP_votes_3nd);

    // Return winning party
    return "democrats";
}
