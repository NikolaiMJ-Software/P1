#include "connecter.h"
#include <time.h>
#define EDUCATION_GROWTH_FACTOR 1.1363636363636
void comprehensibility_function(states state, int comprehensibility, int year);
void minority_and_proportionality_function(states state, double minority_proportionality);
void personalization_function(states* state, candidates* candidate_list, int personalization);
void legitimacy_function(states state, int legitimacy);
void reset(states state);
int dem_electors = 0, rep_electors = 0, third_electors = 0, temp_state_rep_votes, temp_state_dem_votes, temp_state_third_votes;
void parameters(states* state, candidates* candidate_list, int year, double minority_proportionality, int personalization, int legitimacy, int comprehensibility) {
    for (int i = 0; i<STATES; i++) {
        comprehensibility_function(state[i], comprehensibility, year);
        minority_and_proportionality_function(state[i], minority_proportionality);
        legitimacy_function(state[i], legitimacy);
        reset(state[i]);
    }
    personalization_function(state, candidate_list, personalization);
}
void comprehensibility_function(states state, int comprehensibility, int year) {
    double rep_age_lean = 55, dem_age_lean = 45, rep_education_lean = 32, dem_education_lean = 23 + (year - 1999) * EDUCATION_GROWTH_FACTOR;
    double informed_dem_votes = (state.dem_votes + state.rep_votes) * (dem_age_lean / 100 + dem_education_lean / (rep_education_lean + dem_education_lean))/2,
    informed_rep_votes = (state.dem_votes + state.rep_votes) * (rep_age_lean / 100 + rep_education_lean / (rep_education_lean + dem_education_lean))/2;
    temp_state_dem_votes = state.dem_votes;
    temp_state_rep_votes = state.rep_votes;
    state.dem_votes += (informed_dem_votes - state.dem_votes) / 100 * comprehensibility;
    state.rep_votes += (informed_rep_votes - state.rep_votes) / 100 * comprehensibility;

    // side 28 https://download.ssrn.com/23/04/08/ssrn_id4413410_code2576815.pdf?response-content-disposition=inline&X-Amz-Security-Token=IQoJb3JpZ2luX2VjELX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJGMEQCIC064MApJX7ba9dZdwnTkYbVMcM8cRTEtQt2XVXhpkQhAiB3AW%2FtB8Oj6Zel2%2FHEXh8M2GuGzANHg9Nf3c%2BeS24JGCq9BQheEAQaDDMwODQ3NTMwMTI1NyIMF46%2B31Y2TMZbARt0KpoFx5lANk02jioFvARlNiskh6RFDzUFlALkCwFtmXzFcdkT7G8Quq0k%2BIyzhuNWS4phr9GU6Q0JEyc6q9iuWXD8RqIaw2a7YvqXzak6IBVwx4BMWYoaVeQj04uhQJbvNYagLghShP3aw8TaCYE320JfnKtH%2FBq1uGLAtck011tP9dfEHiczw4yLyU3MIVMFZV2JiFU0gqhK964P4h89ek%2FQnBAXb%2FGrS6m6ZJO21kx2BJzQKgrJVaSuSoIGkM14WAnuK6tsnXPoPc74RNQ%2Fdsmpp9KiNtCycMvk5Gl64naqTp%2BvQehTQN0GNjAB6LPI6%2FLQXArGgGxZ5pMkNkUwZQORP%2BOJ39rBPE8TU6uhSAvAsQyaf9tRT5nSWkIR3X5JZHFka2LgMziCKFtTnTXGVswv%2Ff%2B6o92W9H0B6ovJq1lBm%2FvSecIBQswkPuKjNIi8koB%2FyNJd%2BMNts1tos4P6ero5PPuifrF9mi1KciFHCaIs8Tj1c%2FLj0FrBHHuQTkPdRhHZf2Ni%2Bj0qEti4aYunet0tX6eS2o0uxxhH4qAXJoa%2Fz1lwc6jOJ8ikt%2F4BsZBB8bOPvkpH47b5yFl30cOvNzGyqygwzNZt3lj6MIg8KkkErxyOxkVZrWOEQiqEaBrEl79DkoLjmwkgSokdFzjH1vSSonmptOni9c%2B9hvU4Tp5RKg7LkKgxfeZtT8q0P7TztYnP1waAlNRZ6IlbmXQR4xnjHX0UF9MTdYzMPoiRaEso%2FUlSBWcf%2BdLtZ5YsELuQqr0ER5qo19wJa8tmCdj%2FOJ7%2F3r2mxO4rfB7ZI006FfFqR3TqLWrtm3fYRWURxbFh2Wr%2F%2FXFUJ409ya7%2BESo4pAa08tceIVfyMSAfNa03splBLSdiUhPeA%2BjSxW19MOnQoboGOrIBdxZwX%2FUGmmyWRMyLYjmqZWYNikoWbeNQVNTSpnuKtzqw49Am6EH%2Fns%2F%2FXHZukRwVby0mQftRT4S1r94s3hSBWVqlTo34juDhmYtzUyKOthMgSDIl6N%2Bg27ca%2BdcKVZZSknQrkFlsxIYUk8IYNchNe6DzZfxotm4an4kdhlh2cBPkgYjsjmRgATMQuvA7BUz%2BUkDJVLcHfhKetIoGfkNXr9Z53x5xkw0IKke4OPq%2BOPutag%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20241128T135606Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAUPUUPRWEXDROWOE7%2F20241128%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=7d7e6c6dbda7f9394b5a40f5988da349332a3b37a3a9b53d8e11335e5c530d35&abstractId=3593002
    // https://www.pewresearch.org/politics/2024/04/09/age-generational-cohorts-and-party-identification/
    // https://www.americansurveycenter.org/short-reads/a-college-educated-party/
}
void minority_and_proportionality_function(states state, double minority_proportionality) {
    double state_dem_votes = state.dem_votes, state_rep_votes = state.rep_votes, state_third_votes = state.third_votes;
    if (state_dem_votes > state_rep_votes && state_dem_votes > state_third_votes) {
        state_dem_votes = state_dem_votes + state_rep_votes + state_third_votes - (state_rep_votes + state_third_votes) * minority_proportionality / 100;
        state_rep_votes *= minority_proportionality / 100;
        state_third_votes *= minority_proportionality / 100;
    } else if (state_rep_votes > state_dem_votes && state_rep_votes > state_third_votes) {
        state_rep_votes = state_dem_votes + state_rep_votes + state_third_votes - (state_dem_votes + state_third_votes) * minority_proportionality / 100;
        state_dem_votes *= minority_proportionality / 100;
        state_third_votes *= minority_proportionality / 100;
    } else if (state_third_votes > state_dem_votes && state_third_votes > state_rep_votes) {
        state_third_votes = state_dem_votes + state_rep_votes + state_third_votes - (state_rep_votes + state_dem_votes) * minority_proportionality / 100;
        state_rep_votes *= minority_proportionality / 100;
        state_dem_votes *= minority_proportionality / 100;
    }
    int total_votes = state.dem_votes + state.rep_votes + state.third_votes, state_third_electors = 0, state_dem_electors = 0, state_rep_electors = 0, required_votes = total_votes / state.electors;
    while (state_third_votes >= required_votes || state_rep_votes >= required_votes || state_dem_votes >= required_votes) {
        if (state_third_votes >= required_votes) {
            state_third_electors++;
            state_third_votes -= required_votes;
        }
        if (state_rep_votes >= required_votes) {
            state_rep_electors++;
            state_rep_votes -= required_votes;
        }
        if (state_dem_votes >= required_votes) {
            state_dem_electors++;
            state_dem_votes -= required_votes;
        }
    }
    while (1) {
        if (state_third_electors + state_dem_electors + state_rep_electors < state.electors) {
            if (state_third_votes >= state_dem_votes && state_third_votes >= state_rep_electors) {
                state_third_electors++;
            } else if (state_dem_votes >= state_rep_votes && state_dem_votes >= state_third_votes) {
                state_dem_electors++;
            } else if (state_rep_votes >= state_dem_votes && state_rep_votes >= state_third_votes) {
                state_rep_electors++;
            }
        } else {
            break;
        }
    }
    dem_electors += state_dem_electors;
    rep_electors += state_rep_electors;
    third_electors += state_third_electors;
}
void personalization_function(states* state, candidates* candidate_list, int personalization) {
    //rep, dem and third candidate-lists:
    int rep_count = 0, dem_count = 0, third_count = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        if (candidate_list[i].party == 0) {
            rep_count++;
        } else if (candidate_list[i].party == 1) {
            dem_count++;
        } else if (candidate_list[i].party == 2) {
            third_count++;
        }
    }
    candidates rep_candidate_list[rep_count];
    candidates dem_candidate_list[dem_count];
    candidates third_candidate_list[third_count];
    int rep_size, dem_size, third_size;
    for (int i = 0; i < CANDIDATES; i++) {
        if (candidate_list[i].party == 0) {
            rep_candidate_list[rep_size++] = candidate_list[i];
        }else if (candidate_list[i].party == 1) {
            dem_candidate_list[dem_size++] = candidate_list[i];
        }else if (candidate_list[i].party == 2) {
            third_candidate_list[third_size++] = candidate_list[i];
        }
    }
    //Test case
    /*
    for (int i = 0; i < dem_count; i++) {
        printf("Name: %s, Candidacy: %d, P_Popularity: %d, VP_Popularity: %d\n",
               dem_candidate_list[i].name,
               dem_candidate_list[i].candidacy,
               dem_candidate_list[i].p_popularity_percentage,
               dem_candidate_list[i].vp_popularity_percentage);
    }
    */
    //temp values:
    char* president = NULL;
    char* vice_president = NULL;
    //normal system
    if (personalization == 0) {
        if (rep_electors > dem_electors && rep_electors > third_electors) {
            for (int i = 0; i<CANDIDATES; i++) {
                if(candidate_list[i].party == 0) {
                    president = candidate_list[i].name;
                    vice_president = candidate_list[i+1].name;
                    printf("The new President of the United States is: %s\n", president);
                    printf("The New Vice-President of the United States is: %s\n", vice_president);
                    break;
                }
            }
        }else if (dem_electors > third_electors && dem_electors > rep_electors) {
            for (int i = 0; i<CANDIDATES; i++) {
                if(candidate_list[i].party == 1) {
                    president = candidate_list[i].name;
                    vice_president = candidate_list[i+1].name;
                    printf("The new President of the United States is: %s\n", president);
                    printf("The New Vice-President of the United States is: %s\n", vice_president);
                    break;
                }
            }
        }else if (third_electors > rep_electors && third_electors > dem_electors) {
            for (int i = 0; i<CANDIDATES; i++) {
                if(candidate_list[i].party == 3) {
                    president = candidate_list[i].name;
                    vice_president = candidate_list[i+1].name;
                    printf("The new President of the United States is: %s\n", president);
                    printf("The New Vice-President of the United States is: %s\n", vice_president);
                    break;
                }
            }
        }
    }
    //Semi personlized:
    if (personalization == 1) {
        srand(time(NULL));
        int temp_votes= 0;
        for (int i = 0; i<STATES; i++) {
            if (rep_electors > dem_electors && rep_electors > third_electors) {
                temp_votes = state[i].rep_votes;

                for (int j = 0; j<temp_votes; j++) {
                    int random_number = rand() % 100;
                    int p_popularity = 0;

                    for (int k = 0; k < rep_count; k++) {
                        p_popularity += rep_candidate_list[k].p_popularity_percentage;
                        if (random_number < p_popularity) {
                            rep_candidate_list[k].votes++; // Assign vote to candidate
                            break;
                        }
                    }
                }
                printf("State %d (Republican Votes: %d):\n", i + 1, temp_votes);
                for (int j = 0; j < rep_count; j++) {
                    printf("  Candidate: %s, Votes: %d\n",
                           rep_candidate_list[j].name,
                           rep_candidate_list[j].votes);
                }

                // Distribute votes for Vice President
                for (int j = 0; j < temp_votes; j++) {
                    int random_number = rand() % 100;
                    int vp_popularity = 0;

                    for (int k = 0; k < rep_count; k++) {
                        vp_popularity += rep_candidate_list[k].vp_popularity_percentage;
                        if (random_number < vp_popularity) {
                            rep_candidate_list[k].votes++; // Assign VP vote to candidate
                            break;
                        }
                    }
                }
                // Print results for Vice Presidential votes
                printf("State %d (Republican Vice Presidential Votes: %d):\n", i + 1, temp_votes);
                for (int j = 0; j < rep_count; j++) {
                    printf("  Candidate: %s, Vice Presidential Votes: %d\n",
                           rep_candidate_list[j].name,
                           rep_candidate_list[j].votes);
                }
            }

        }
    }
        if (personalization == 2) {

        }
        if (personalization == 3) {
        }
    }

void legitimacy_function(states state, int legitimacy) {

}
void reset(states state) {
    state.dem_votes = temp_state_dem_votes, state.rep_votes = temp_state_rep_votes;
    dem_electors = 0, rep_electors = 0, third_electors = 0, temp_state_rep_votes = 0, temp_state_dem_votes = 0;
}