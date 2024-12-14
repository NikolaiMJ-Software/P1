#include "../connecter.h"
#define EDUCATION_GROWTH_FACTOR 1.1363636363636
//Prototypes
void comprehensibility_function(states state, int comprehensibility, int year);
void minority_and_proportionality_function(states state, double minority_proportionality);
void personalization_function(states* state, candidates* candidate_list, int personalization);
void legitimacy_function(states* state, int legitimacy);
int dem_electors, rep_electors, third_electors, temp_state_third_votes, fully_trusts, somewhat_trusts, slightly_trusts, doesnt_trust;
void parameters(states* state, candidates* candidate_list, int year, int states_abolished) {

    // A list of variables for all states are reset at the beginning of the code.
    dem_electors = 0, rep_electors = 0, third_electors = 0, doesnt_trust = 0, slightly_trusts = 0, somewhat_trusts = 0, fully_trusts = 0;
    int personalization = 0, legitimacy = 0, comprehensibility = 0;
    double minority_proportionality = 0;

    // Data regarding every variable which is gotten from the user.
    printf("You have chosen to customize the US Electoral System\n");
    while(1) {
        fflush(stdout);
        printf("First lets choose an int between 0-100 (base is 50), to determine the amount of informed voters:\n");
        if (scanf("%d", &comprehensibility) == 1 && comprehensibility >= 0 && comprehensibility <= 100) {
            break;
        } else {
            printf("Invalid input try again!\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
    while(1) {
        fflush(stdout);
        printf("Now to choose how proportional your system will be, choose an int between 0-100 (base is 0):\n");
        if (scanf("%lf", &minority_proportionality) == 1 && minority_proportionality >= 0 && minority_proportionality <= 100) {
            break;
        } else {
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
        } else {
            printf("Invalid input try again!\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }

    // The main function then calls each of the functions.
    for (int i = 0; i<STATES; i++) {
        //The functions use the US_election_data to calculate electors for each state depending on variables.
        comprehensibility_function(state[i], comprehensibility, year);
        minority_and_proportionality_function(state[i], minority_proportionality);
        if (states_abolished) {
            break;
        }
    }
    // These functions then interpret the outcome based on the electors.
    personalization_function(state, candidate_list, personalization);
    legitimacy_function(state, legitimacy);
}

void comprehensibility_function(states state, int comprehensibility, int year) {
    // This function changes the average to either sway towards, or away from, the most informed voters, depending on comprehensibility variable.
    double rep_age_lean = 55, dem_age_lean = 45, rep_education_lean = 32, dem_education_lean = 23 + (year - 1999) * EDUCATION_GROWTH_FACTOR;
    double informed_dem_votes = (state.dem_votes + state.rep_votes) * (dem_age_lean / 100 + dem_education_lean / (rep_education_lean + dem_education_lean))/2,
    informed_rep_votes = (state.dem_votes + state.rep_votes) * (rep_age_lean / 100 + rep_education_lean / (rep_education_lean + dem_education_lean))/2;
    state.dem_votes += (informed_dem_votes - state.dem_votes) / 100 * (-100 + comprehensibility * 2);
    state.rep_votes += (informed_rep_votes - state.rep_votes) / 100 * (-100 + comprehensibility * 2);
}

void minority_and_proportionality_function(states state, double minority_proportionality) {
    // This function calculates the amount of electors for each state using their votes, and minority_proportionality variable, to simulate how proportional the electors are given from the votes.
    // First the votes are changed depending on how much proportionality we want to introduce as a percentage.
    // For example, if proportionality is 0, all votes go to the winning party in a state, and if 100, they are completely proportional. If 50, somewhere between the two.
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

    // Electors are then distributed according to a proportional method.
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

    // The amount of electors for the state, are then added to the global amount of electors the party has.
    dem_electors += state_dem_electors;
    rep_electors += state_rep_electors;
    third_electors += state_third_electors;
}

void personalization_function(states* state, candidates* candidate_list, int personalization) {
    // Rep, dem and third candidate-lists creation
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

    // Temp values:
    char* president = NULL;
    char* vice_president = NULL;
    // Normal system where the winning parties main candidates become president and vice president
    if (personalization == 0) {
        // Checking which elector count is largest
        // Selecting first candidate which party is 0 (republican), and then the next on the list for vice president
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
            // Selecting first candidate which party is 1 (democrats), and then the next on the list for vice president
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
            // Selecting first candidate which party is 2 (third party), and then the next on the list for vice president
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
    // Semi personlized where you select a candidate based on their popularity procentage
    int max_p_votes = -1;
    int max_vp_votes = -1;
    // Making empty lists
    candidates* President = NULL;
    candidates* Vice_President = NULL;
    if (personalization == 1) {
        srand(time(NULL)); // Random value
        int temp_votes= 0;
        // Checking votes for each vice president and president from each state to calculate their overall vote based on popularity percentage
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
        // Calculating which elector from winning party is the one with most votes
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
        // Buffers to hold formatted numbers
        char formatted_p_votes[30] = "";
        char formatted_vp_votes[30] = "";
        // Return voters with commas
        format_number(max_p_votes, formatted_p_votes);
        format_number(max_vp_votes, formatted_vp_votes);
        // Display results
        printf("Election Results:\n");
        printf("Presidential Winner: %s with %s votes\n", President->name, formatted_p_votes);
        printf("Vice Presidential Winner: %s with %s votes\n", Vice_President->name, formatted_vp_votes);
    }
}

void legitimacy_function(states* state, int legitimacy) {
    // This functions determines how many voters of non-winning parties trust the election based on the legitimacy variable.

    // Firstly a set of variables, that determine the average amount of trust in the system after losing the election are set up.
    int rep_high_trust = 18, rep_med_trust = 26, rep_low_trust = 22, rep_no_trust = 34, dem_high_trust = 45, dem_med_trust = 34, dem_low_trust = 11, dem_no_trust = 10,
    third_high_trust = (rep_high_trust+dem_high_trust)/2, third_med_trust = (rep_med_trust+dem_med_trust)/2, third_low_trust = (rep_low_trust+dem_low_trust)/2, third_no_trust = (rep_no_trust+dem_no_trust)/2;

    // According to the legitimacy variable, the scores for trust in the election are skewed.
    // If legitimacy is higher then 50 it takes trust points away from the lower categories (no/lower trust) and adds them to the higher categories (medium/high trust)
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
        // If legitimacy is lower than 50, the opposite happens
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

    // The amount of voters that feel different levels of trust, are then calculated based on population of each state and skewed trust values.
    for (int i = 0; i < STATES; i++) {
        if (state[i].dem_votes == 0 && state[i].rep_votes == 0 && state[i].third_votes == 0) {
            continue; // Skip zero-vote states
        }
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
    }

    // Lastly we have a summary of the data from all states, and the data from this function, that are shown to the user.
    if (dem_electors > rep_electors && dem_electors > third_electors) {
        printf("This democratic president won with %d electors", dem_electors);
    } else if (rep_electors > dem_electors && rep_electors > third_electors) {
        printf("This republican president won with %d electors", rep_electors);
    } else if (third_electors > dem_electors && third_electors > rep_electors) {
        printf("This third party president won with %d electors", third_electors);
    }
    // Buffers to hold formatted numbers
    char doesnt_t_votes[30] = "";
    char slightly_t_votes[30] = "";
    char somewhat_t_votes[30] = "";
    char fully_t_votes[30] = "";
    // Return voters with commas
    format_number(doesnt_trust, doesnt_t_votes);
    format_number(slightly_trusts, slightly_t_votes);
    format_number(somewhat_trusts, somewhat_t_votes);
    format_number(fully_trusts, fully_t_votes);
    printf("\nIn the opposing parties, there are %s voters that don't trust the outcome,\n%s voters that only slightly trust it, %s voters that somewhat trust it,\nand %s voters that fully trust it.\n\n", doesnt_t_votes, slightly_t_votes, somewhat_t_votes, fully_t_votes);
}