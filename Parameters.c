#include "connecter.h"
void comprehensibility_function(states state, int comprehensibility);
void minority_and_proportionality_function(states state, double minority_proportionality);
void personalization_function(states state, candidates* candidate_list, int personalization);
void legitimacy_function(states state, int legitimacy);
int dem_electors = 0, rep_electors = 0, third_electors = 0;
void parameters(states* state, candidates* candidate_list, double minority_proportionality, int personalization, int legitimacy, int comprehensibility) {
    for (int i = 0; i<STATES; i++) {
        comprehensibility_function(state[i], comprehensibility);
        minority_and_proportionality_function(state[i], minority_proportionality);
        personalization_function(state[i], candidate_list, personalization);
        legitimacy_function(state[i], legitimacy);
    }
}
void comprehensibility_function(states state, int comprehensibility) {
    //https://www.pbs.org/newshour/show/how-a-college-degree-is-one-of-the-best-predictors-of-which-candidate-voters-support
    // side 28 https://download.ssrn.com/23/04/08/ssrn_id4413410_code2576815.pdf?response-content-disposition=inline&X-Amz-Security-Token=IQoJb3JpZ2luX2VjELX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJGMEQCIC064MApJX7ba9dZdwnTkYbVMcM8cRTEtQt2XVXhpkQhAiB3AW%2FtB8Oj6Zel2%2FHEXh8M2GuGzANHg9Nf3c%2BeS24JGCq9BQheEAQaDDMwODQ3NTMwMTI1NyIMF46%2B31Y2TMZbARt0KpoFx5lANk02jioFvARlNiskh6RFDzUFlALkCwFtmXzFcdkT7G8Quq0k%2BIyzhuNWS4phr9GU6Q0JEyc6q9iuWXD8RqIaw2a7YvqXzak6IBVwx4BMWYoaVeQj04uhQJbvNYagLghShP3aw8TaCYE320JfnKtH%2FBq1uGLAtck011tP9dfEHiczw4yLyU3MIVMFZV2JiFU0gqhK964P4h89ek%2FQnBAXb%2FGrS6m6ZJO21kx2BJzQKgrJVaSuSoIGkM14WAnuK6tsnXPoPc74RNQ%2Fdsmpp9KiNtCycMvk5Gl64naqTp%2BvQehTQN0GNjAB6LPI6%2FLQXArGgGxZ5pMkNkUwZQORP%2BOJ39rBPE8TU6uhSAvAsQyaf9tRT5nSWkIR3X5JZHFka2LgMziCKFtTnTXGVswv%2Ff%2B6o92W9H0B6ovJq1lBm%2FvSecIBQswkPuKjNIi8koB%2FyNJd%2BMNts1tos4P6ero5PPuifrF9mi1KciFHCaIs8Tj1c%2FLj0FrBHHuQTkPdRhHZf2Ni%2Bj0qEti4aYunet0tX6eS2o0uxxhH4qAXJoa%2Fz1lwc6jOJ8ikt%2F4BsZBB8bOPvkpH47b5yFl30cOvNzGyqygwzNZt3lj6MIg8KkkErxyOxkVZrWOEQiqEaBrEl79DkoLjmwkgSokdFzjH1vSSonmptOni9c%2B9hvU4Tp5RKg7LkKgxfeZtT8q0P7TztYnP1waAlNRZ6IlbmXQR4xnjHX0UF9MTdYzMPoiRaEso%2FUlSBWcf%2BdLtZ5YsELuQqr0ER5qo19wJa8tmCdj%2FOJ7%2F3r2mxO4rfB7ZI006FfFqR3TqLWrtm3fYRWURxbFh2Wr%2F%2FXFUJ409ya7%2BESo4pAa08tceIVfyMSAfNa03splBLSdiUhPeA%2BjSxW19MOnQoboGOrIBdxZwX%2FUGmmyWRMyLYjmqZWYNikoWbeNQVNTSpnuKtzqw49Am6EH%2Fns%2F%2FXHZukRwVby0mQftRT4S1r94s3hSBWVqlTo34juDhmYtzUyKOthMgSDIl6N%2Bg27ca%2BdcKVZZSknQrkFlsxIYUk8IYNchNe6DzZfxotm4an4kdhlh2cBPkgYjsjmRgATMQuvA7BUz%2BUkDJVLcHfhKetIoGfkNXr9Z53x5xkw0IKke4OPq%2BOPutag%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20241128T135606Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAUPUUPRWEXDROWOE7%2F20241128%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=7d7e6c6dbda7f9394b5a40f5988da349332a3b37a3a9b53d8e11335e5c530d35&abstractId=3593002
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
        state_third_votes = state_dem_votes + state_rep_votes + state_third_votes - (state.rep_votes + state.dem_votes) * minority_proportionality / 100;
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
        if (state_third_electors + state_dem_electors + state_rep_electors > state.electors) {
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
void personalization_function(states state, candidates* candidate_list, int personalization) {
    //temp values:
    int rep_electors = 270, dem_electors = 218, third_electors = 50;
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
                }
            }
        }else if (third_electors > rep_electors && third_electors > dem_electors) {
            for (int i = 0; i<CANDIDATES; i++) {
                if(candidate_list[i].party == 3) {
                    president = candidate_list[i].name;
                    vice_president = candidate_list[i+1].name;
                    printf("The new President of the United States is: %s\n", president);
                    printf("The New Vice-President of the United States is: %s\n", vice_president);
                }
            }
        }
    }
}
void legitimacy_function(states state, int legitimacy) {

}