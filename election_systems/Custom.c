#include "../connecter.h"
#include <time.h>
#define EDUCATION_GROWTH_FACTOR 1.1363636363636

//Prototypes
void comprehensibility_function(states state, int comprehensibility, int year);
void minority_and_proportionality_function(states state, double minority_proportionality);
void personalization_function(states* state, candidates* candidate_list, int personalization);
void legitimacy_function(states* state, int legitimacy);
int dem_electors, rep_electors, third_electors, temp_state_third_votes, fully_trusts, somewhat_trusts, slightly_trusts, doesnt_trust;
void parameters(states* state, candidates* candidate_list, int year, int states_abolished) {

    //A list of variables for all states are reset at the beginning of the code.
    dem_electors = 0, rep_electors = 0, third_electors = 0, doesnt_trust = 0, slightly_trusts = 0, somewhat_trusts = 0, fully_trusts = 0;
    int personalization = 0, legitimacy = 0, comprehensibility = 0;
    double minority_proportionality = 0;

    //Data regarding every variable which is gotten from the user.
    printf("You have chosen to customize the US Electoral System\n");
    while(1) {
        fflush(stdout);
        printf("First lets choose an int between 0-100 (base is 50), to determine the amount of informed voters:\n");
        if (scanf("%d", &comprehensibility) == 1 && comprehensibility >= 0 && comprehensibility <= 100) {
            break;
        }else {
            printf("Invalid input try again!\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
    while(1) {
        fflush(stdout);
        printf("Now to choose how proportional your system will be, choose an int between 0-100 (base is 0):\n");
        if (scanf("%lf", &minority_proportionality) == 1 && minority_proportionality >= 0 && minority_proportionality <= 100) {
            break;
        }else {
            printf("Invalid input try again!\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
    while(1) {
        fflush(stdout);
        char input[10];
        printf("Now choose if the system should be more personalized, which would mean the voters would be allowed to vote for their\npresident of choice, instead of a pre selected one (yes/no):\n");
        scanf("%s", &input);
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }
        if (strcmp(input, "yes") == 0 ||strcmp(input, "y") == 0) {
            personalization = 1;
            break;
        } else if (strcmp(input, "no") == 0 || strcmp(input, "n") == 0) {
            personalization = 0;
            break;
        } else {
            printf("Invalid input. Please enter 'yes' or 'no'.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
    while(1) {
        fflush(stdout);
        printf("Lastly pick the legitimacy of your system, to determine the amount of satisfied voters from the opposing parties,\nby giving an int from 0-100 (base is 50):\n");
        if (scanf("%d", &legitimacy) == 1 && legitimacy >= 0 && legitimacy <= 100) {
            break;
        }else {
            printf("Invalid input try again!\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }

    //The main function then calls each of the functions.
    for (int i = 0; i<STATES; i++) {
        //The functions use the US_election_data to calculate electors for each state depending on variables.
        comprehensibility_function(state[i], comprehensibility, year);
        minority_and_proportionality_function(state[i], minority_proportionality);
        if (states_abolished) {
            break;
        }
    }
    //These functions then interpret the outcome based on the electors.
    personalization_function(state, candidate_list, personalization);
    legitimacy_function(state, legitimacy);
}

void comprehensibility_function(states state, int comprehensibility, int year) {

    //This function changes the average to either sway towards, or away from, the most informed voters, depending on comprehensibility variable.
    double rep_age_lean = 55, dem_age_lean = 45, rep_education_lean = 32, dem_education_lean = 23 + (year - 1999) * EDUCATION_GROWTH_FACTOR;
    double informed_dem_votes = (state.dem_votes + state.rep_votes) * (dem_age_lean / 100 + dem_education_lean / (rep_education_lean + dem_education_lean))/2,
    informed_rep_votes = (state.dem_votes + state.rep_votes) * (rep_age_lean / 100 + rep_education_lean / (rep_education_lean + dem_education_lean))/2;
    state.dem_votes += (informed_dem_votes - state.dem_votes) / 100 * (-100 + comprehensibility * 2);
    state.rep_votes += (informed_rep_votes - state.rep_votes) / 100 * (-100 + comprehensibility * 2);

    // side 28 https://download.ssrn.com/23/04/08/ssrn_id4413410_code2576815.pdf?response-content-disposition=inline&X-Amz-Security-Token=IQoJb3JpZ2luX2VjELX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJGMEQCIC064MApJX7ba9dZdwnTkYbVMcM8cRTEtQt2XVXhpkQhAiB3AW%2FtB8Oj6Zel2%2FHEXh8M2GuGzANHg9Nf3c%2BeS24JGCq9BQheEAQaDDMwODQ3NTMwMTI1NyIMF46%2B31Y2TMZbARt0KpoFx5lANk02jioFvARlNiskh6RFDzUFlALkCwFtmXzFcdkT7G8Quq0k%2BIyzhuNWS4phr9GU6Q0JEyc6q9iuWXD8RqIaw2a7YvqXzak6IBVwx4BMWYoaVeQj04uhQJbvNYagLghShP3aw8TaCYE320JfnKtH%2FBq1uGLAtck011tP9dfEHiczw4yLyU3MIVMFZV2JiFU0gqhK964P4h89ek%2FQnBAXb%2FGrS6m6ZJO21kx2BJzQKgrJVaSuSoIGkM14WAnuK6tsnXPoPc74RNQ%2Fdsmpp9KiNtCycMvk5Gl64naqTp%2BvQehTQN0GNjAB6LPI6%2FLQXArGgGxZ5pMkNkUwZQORP%2BOJ39rBPE8TU6uhSAvAsQyaf9tRT5nSWkIR3X5JZHFka2LgMziCKFtTnTXGVswv%2Ff%2B6o92W9H0B6ovJq1lBm%2FvSecIBQswkPuKjNIi8koB%2FyNJd%2BMNts1tos4P6ero5PPuifrF9mi1KciFHCaIs8Tj1c%2FLj0FrBHHuQTkPdRhHZf2Ni%2Bj0qEti4aYunet0tX6eS2o0uxxhH4qAXJoa%2Fz1lwc6jOJ8ikt%2F4BsZBB8bOPvkpH47b5yFl30cOvNzGyqygwzNZt3lj6MIg8KkkErxyOxkVZrWOEQiqEaBrEl79DkoLjmwkgSokdFzjH1vSSonmptOni9c%2B9hvU4Tp5RKg7LkKgxfeZtT8q0P7TztYnP1waAlNRZ6IlbmXQR4xnjHX0UF9MTdYzMPoiRaEso%2FUlSBWcf%2BdLtZ5YsELuQqr0ER5qo19wJa8tmCdj%2FOJ7%2F3r2mxO4rfB7ZI006FfFqR3TqLWrtm3fYRWURxbFh2Wr%2F%2FXFUJ409ya7%2BESo4pAa08tceIVfyMSAfNa03splBLSdiUhPeA%2BjSxW19MOnQoboGOrIBdxZwX%2FUGmmyWRMyLYjmqZWYNikoWbeNQVNTSpnuKtzqw49Am6EH%2Fns%2F%2FXHZukRwVby0mQftRT4S1r94s3hSBWVqlTo34juDhmYtzUyKOthMgSDIl6N%2Bg27ca%2BdcKVZZSknQrkFlsxIYUk8IYNchNe6DzZfxotm4an4kdhlh2cBPkgYjsjmRgATMQuvA7BUz%2BUkDJVLcHfhKetIoGfkNXr9Z53x5xkw0IKke4OPq%2BOPutag%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20241128T135606Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAUPUUPRWEXDROWOE7%2F20241128%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=7d7e6c6dbda7f9394b5a40f5988da349332a3b37a3a9b53d8e11335e5c530d35&abstractId=3593002
    // https://www.pewresearch.org/politics/2024/04/09/age-generational-cohorts-and-party-identification/
    // https://www.americansurveycenter.org/short-reads/a-college-educated-party/
}

void minority_and_proportionality_function(states state, double minority_proportionality) {
    //This function calculates the amount of electors for each state using their votes, and minority_proportionality variable, to simulate how proportional the electors are given from the votes.

    //First the votes are changed depending on how much proportionality we want to introduce as a percentage.
    //For example, if proportionality is 0, all votes go to the winning party in a state, and if 100, they are completely proportional. If 50, somewhere between the two.
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

    //Electors are then distributed according to a proportional method.
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

    //The amount of electors for the state, are then added to the global amount of electors the party has.
    dem_electors += state_dem_electors;
    rep_electors += state_rep_electors;
    third_electors += state_third_electors;
}

void personalization_function(states* state, candidates* candidate_list, int personalization) {
    //rep, dem and third candidate-lists creation
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
    int rep_size = 0, dem_size = 0, third_size = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        if (candidate_list[i].party == 0) {
            rep_candidate_list[rep_size++] = candidate_list[i];
        }else if (candidate_list[i].party == 1) {
            dem_candidate_list[dem_size++] = candidate_list[i];
        }else if (candidate_list[i].party == 2) {
            third_candidate_list[third_size++] = candidate_list[i];
        }
    }

    //temp values:
    char* president = NULL;
    char* vice_president = NULL;
    //normal system where the winning parties main candidates become president and vice president
    if (personalization == 0) {
        //checking which elector count is largest
        //selecting first candidate which party is 0 (republican), and then the next on the list for vice president
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
            //selecting first candidate which party is 1 (democrats), and then the next on the list for vice president
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
            //selecting first candidate which party is 2 (third party), and then the next on the list for vice president
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
    //Semi personlized where you select a candidate based on their popularity procentage
    int max_p_votes = -1;
    int max_vp_votes = -1;
    //making empty lists
    candidates* President = NULL;
    candidates* Vice_President = NULL;
    if (personalization == 1) {
        srand(time(NULL)); //random value
        int temp_votes= 0;
        //checking votes for each vice president and president from each state to calculate their overall vote based on popularity percentage
        for (int i = 0; i<STATES; i++) {
            if (rep_electors > dem_electors && rep_electors > third_electors) {
                temp_votes = state[i].rep_votes;
                // Distribute votes for President
                for (int j = 0; j<temp_votes; j++) {
                    int random_number = rand() % 100;
                    int p_popularity = 0;

                    for (int k = 0; k < rep_count; k++) {
                        p_popularity += rep_candidate_list[k].p_popularity_percentage;
                        if (random_number < p_popularity) {
                            rep_candidate_list[k].p_votes++; // Assign vote to candidate
                            break;
                        }
                    }
                }

                // Distribute votes for Vice President
                for (int j = 0; j < temp_votes; j++) {
                    int random_number = rand() % 100;
                    int vp_popularity = 0;

                    for (int k = 0; k < rep_count; k++) {
                        vp_popularity += rep_candidate_list[k].vp_popularity_percentage;
                        if (random_number < vp_popularity) {
                            rep_candidate_list[k].vp_votes++; // Assign VP vote to candidate
                            break;
                        }
                    }
                }
            }
            if (dem_electors > rep_electors && dem_electors > third_electors) {
                temp_votes = state[i].dem_votes;
                // Distribute votes for President
                for (int j = 0; j<temp_votes; j++) {
                    int random_number = rand() % 100;
                    int p_popularity = 0;

                    for (int k = 0; k < dem_count; k++) {
                        p_popularity += dem_candidate_list[k].p_popularity_percentage;
                        if (random_number < p_popularity) {
                            dem_candidate_list[k].p_votes++; // Assign vote to candidate
                            break;
                        }
                    }
                }

                // Distribute votes for Vice President
                for (int j = 0; j < temp_votes; j++) {
                    int random_number = rand() % 100;
                    int vp_popularity = 0;

                    for (int k = 0; k < dem_count; k++) {
                        vp_popularity += dem_candidate_list[k].vp_popularity_percentage;
                        if (random_number < vp_popularity) {
                            dem_candidate_list[k].vp_votes++; // Assign VP vote to candidate
                            break;
                        }
                    }
                }
            }
            if (third_electors > dem_electors && third_electors > rep_electors) {
                temp_votes = state[i].third_votes;
                // Distribute votes for President
                for (int j = 0; j<temp_votes; j++) {
                    int random_number = rand() % 100;
                    int p_popularity = 0;

                    for (int k = 0; k < third_count; k++) {
                        p_popularity += third_candidate_list[k].p_popularity_percentage;
                        if (random_number < p_popularity) {
                            third_candidate_list[k].p_votes++; // Assign vote to candidate
                            break;
                        }
                    }
                }

                // Distribute votes for Vice President
                for (int j = 0; j < temp_votes; j++) {
                    int random_number = rand() % 100;
                    int vp_popularity = 0;

                    for (int k = 0; k < third_count; k++) {
                        vp_popularity += third_candidate_list[k].vp_popularity_percentage;
                        if (random_number < vp_popularity) {
                            third_candidate_list[k].vp_votes++; // Assign VP vote to candidate
                            break;
                        }
                    }
                }
            }

        }
        //calculating which elector from winning party is the one with most votes
        if (rep_electors > dem_electors && rep_electors > third_electors) {
            for (int i = 0; i < rep_count; i++) {
                if (rep_candidate_list[i].p_votes > max_p_votes) {
                    max_p_votes = rep_candidate_list[i].p_votes;
                    President = &rep_candidate_list[i];
                }
                if (rep_candidate_list[i].vp_votes > max_vp_votes) {
                    max_vp_votes = rep_candidate_list[i].vp_votes;
                    Vice_President = &rep_candidate_list[i];
                }
            }
        }
        if (dem_electors > rep_electors && dem_electors > third_electors) {
            for (int i = 0; i < dem_count; i++) {
                if (dem_candidate_list[i].p_votes > max_p_votes) {
                    max_p_votes = dem_candidate_list[i].p_votes;
                    President = &dem_candidate_list[i];
                }
                if (dem_candidate_list[i].vp_votes > max_vp_votes) {
                    max_vp_votes = dem_candidate_list[i].vp_votes;
                    Vice_President = &dem_candidate_list[i];
                }
            }
        }
        if (third_electors > dem_electors && third_electors > rep_electors) {
            for (int i = 0; i < third_count; i++) {
                if (third_candidate_list[i].p_votes > max_p_votes) {
                    max_p_votes = third_candidate_list[i].p_votes;
                    President = &third_candidate_list[i];
                }
                if (third_candidate_list[i].vp_votes > max_vp_votes) {
                    max_vp_votes = third_candidate_list[i].vp_votes;
                    Vice_President = &third_candidate_list[i];
                }
            }
        }
        // Display results
        printf("Election Results:\n");
        printf("Presidential Winner: %s with %d votes\n", President->name, max_p_votes);
        printf("Vice Presidential Winner: %s with %d votes\n", Vice_President->name, max_vp_votes);
    }
}

void legitimacy_function(states* state, int legitimacy) {
    //This functions determines how many voters of non-winning parties trust the election based on the legitimacy variable.

    //Firstly a set of variables, that determine the average amount of trust in the system after losing the election are set up.
    int rep_high_trust = 18, rep_med_trust = 26, rep_low_trust = 22, rep_no_trust = 34, dem_high_trust = 45, dem_med_trust = 34, dem_low_trust = 11, dem_no_trust = 10,
    third_high_trust = (rep_high_trust+dem_high_trust)/2, third_med_trust = (rep_med_trust+dem_med_trust)/2, third_low_trust = (rep_low_trust+dem_low_trust)/2, third_no_trust = (rep_no_trust+dem_no_trust)/2;

    //according to the legitimacy variable, the scores for trust in the election are skewed.
    //if legitimacy is higher then 50 it takes trust points away from the lower categories (no/lower trust) and adds them to the higher categories (medium/high trust)
    if (legitimacy > 50) {
        for (int i = legitimacy; i >= 50; i--) {
            if (rep_no_trust > 0) {
                rep_no_trust--;
                rep_med_trust++;
            }
            if (dem_no_trust > 0) {
                dem_no_trust--;
                dem_med_trust++;
            }
            if (third_no_trust > 0) {
                third_no_trust--;
                third_med_trust++;
            }
            if (dem_low_trust > 0) {
                dem_low_trust--;
                dem_high_trust++;
            }
            if (rep_low_trust > 0) {
                rep_low_trust--;
                rep_high_trust++;
            }
            if (third_low_trust > 0) {
                third_low_trust--;
                third_high_trust++;
            }
            if ((dem_no_trust == 0 && dem_low_trust == 0)|| (rep_no_trust == 0 && rep_low_trust == 0) || (third_no_trust == 0 && third_low_trust == 0)) {
                if (dem_electors > rep_electors && dem_electors > third_electors) {
                    dem_high_trust++;
                    dem_med_trust--;
                } else if (rep_electors > dem_electors && rep_electors > third_electors) {
                    rep_high_trust++;
                    rep_med_trust--;
                } else if (third_electors > dem_electors && third_electors > rep_electors) {
                    third_high_trust++;
                    third_med_trust--;
                }
            }
        }
        //if legitimacy is lower than 50, the opposite happens
    } else if (legitimacy < 50) {
        for (int i = legitimacy; i <= 50; i++) {
            if (rep_high_trust > 0) {
                rep_high_trust--;
                rep_low_trust++;
            }
            if (dem_high_trust > 0) {
                dem_high_trust--;
                dem_low_trust++;
            }
            if (third_high_trust > 0) {
                third_high_trust--;
                third_low_trust++;
            }
            if (rep_med_trust > 0) {
                rep_med_trust--;
                rep_no_trust++;
            }
            if (dem_med_trust > 0) {
                dem_med_trust--;
                dem_no_trust++;
            }
            if (third_med_trust > 0) {
                third_med_trust--;
                third_no_trust++;
            }
            if ((dem_high_trust == 0 && dem_med_trust == 0)|| (rep_high_trust == 0 && rep_med_trust == 0) || (third_high_trust == 0 && third_med_trust == 0)) {
                if (dem_electors > rep_electors && dem_electors > third_electors) {
                    dem_no_trust++;
                    dem_low_trust--;
                } else if (rep_electors > dem_electors && rep_electors > third_electors) {
                    rep_no_trust++;
                    rep_low_trust--;
                } else if (third_electors > dem_electors && third_electors > rep_electors) {
                    third_no_trust++;
                    third_low_trust--;
                }
            }
        }
    }

    //The amount of voters that feel different levels of trust, are then calculated based on population of each state and skewed trust values.
    for (int i = 0; i < STATES; i++) {
        if (state[i].dem_votes == 0 && state[i].rep_votes == 0 && state[i].third_votes == 0) {
            continue; // Skip zero-vote states
        }
        //printf("trust values: %d %d %d %d\n", fully_trusts, somewhat_trusts, slightly_trusts, doesnt_trust);
        if (dem_electors > rep_electors && dem_electors > third_electors) {
            fully_trusts += (state[i].rep_votes * rep_high_trust + state[i].third_votes * third_high_trust) / 100;
            somewhat_trusts += (state[i].rep_votes * rep_med_trust + state[i].third_votes * third_med_trust) / 100;
            slightly_trusts += (state[i].rep_votes * rep_low_trust + state[i].third_votes * third_low_trust) / 100;
            doesnt_trust += (state[i].rep_votes * rep_no_trust + state[i].third_votes * third_no_trust) / 100;
        } else if (rep_electors > dem_electors && rep_electors > third_electors) {
            fully_trusts += (state[i].dem_votes * dem_high_trust + state[i].third_votes * third_high_trust) / 100;
            somewhat_trusts += (state[i].dem_votes * dem_med_trust + state[i].third_votes * third_med_trust) / 100;
            slightly_trusts += (state[i].dem_votes * dem_low_trust + state[i].third_votes * third_low_trust) / 100;
            doesnt_trust += (state[i].dem_votes * dem_no_trust + state[i].third_votes * third_no_trust) / 100;
        } else if (third_electors > dem_electors && third_electors > rep_electors) {
            fully_trusts += (state[i].dem_votes * dem_high_trust + state[i].rep_votes * rep_high_trust) / 100;
            somewhat_trusts += (state[i].dem_votes * dem_med_trust + state[i].rep_votes * rep_med_trust) / 100;
            slightly_trusts += (state[i].dem_votes * dem_low_trust + state[i].rep_votes * rep_low_trust) / 100;
            doesnt_trust += (state[i].dem_votes * dem_no_trust + state[i].rep_votes * rep_no_trust) / 100;
        }
        // Tests for this function.
        //printf("trust values: %d %d %d %d\n", fully_trusts, somewhat_trusts, slightly_trusts, doesnt_trust);
        // printf("Trust factors: rep_high=%d, rep_med=%d, rep_low=%d, rep_no=%d, third_high=%d, third_med=%d, third_low=%d, third_no=%d\n",
        // rep_high_trust, rep_med_trust, rep_low_trust, rep_no_trust, third_high_trust, third_med_trust, third_low_trust, third_no_trust);
        // printf("Votes: rep=%d, dem=%d, third=%d\n", state[0].rep_votes, state[0].dem_votes, state[0].third_votes);
    }

    //Lastly we have a summary of the data from all states, and the data from this function, that are shown to the user.
    if (dem_electors > rep_electors && dem_electors > third_electors) {
        printf("This democratic president won with %d of the electors", dem_electors);
    } else if (rep_electors > dem_electors && rep_electors > third_electors) {
        printf("This republican president won with %d of the electors", rep_electors);
    } else if (third_electors > dem_electors && third_electors > rep_electors) {
        printf("This third party president won with %d of the electors", third_electors);
    }
    printf("\nIn the opposing parties, there are %u that don't trust the outcome, %u that only slightly trust it, %u that somewhat trust it, and %u that fully trust it\n\n", doesnt_trust, slightly_trusts, somewhat_trusts, fully_trusts);
    // https://www.pewresearch.org/politics/2024/11/22/americans-feelings-about-the-state-of-the-nation-reactions-to-the-2024-election/
}