#include "connecter.h"
int main(void) {
    int first_run = 0;
    printUSA();
    const char* directory = "US_election_data";
    // Allocate memory for the array cap_systems
    cmp* cap_systems = malloc(NO_SYSTEMS * sizeof(cmp));
    if (cap_systems == NULL) {
        // Error handling if memory allocation fails
        printf("Memory allocation failed!\n");
        return 1;
    }
    cmp* uncap_systems = malloc(NO_SYSTEMS * sizeof(cmp));
    if (uncap_systems == NULL) {
        // Error handling if memory allocation fails
        printf("Memory allocation failed!\n");
        exit (EXIT_FAILURE);
    }
    // Empty both arrays
    memset(cap_systems, 0, NO_SYSTEMS * sizeof(cmp));
    memset(uncap_systems, 0, NO_SYSTEMS * sizeof(cmp));
    while(true) {
        int uncapped = 0;
        list_available_files(directory);

        fflush(stdin);
        int input_year;
        char wyoming_rule_true[10];
        char system[10] = "original";
        char abolish_states_true[10];
        int states_abolished = 0;

        // Allocate memory for the array USA
        states* USA = malloc(STATES * sizeof(states));
        if (USA == NULL) {
            // Error handling if memory allocation fails
            printf("Memory allocation failed!\n");
            return 1;
        }

        // Check if cap_systems and uncap_systems is full
        int full_cap_systems = 0;
        int full_uncap_systems = 0;
        for (int i = 0; i < NO_SYSTEMS; i++) {
            // Cap_system
            if (cap_systems[i].DEM_electors > 0 || cap_systems[i].REP_electors > 0 || cap_systems[i].TP_electors > 0) {
                full_cap_systems++;
            }
            // Uncap system
            if (uncap_systems[i].DEM_electors > 0 || uncap_systems[i].REP_electors > 0 || uncap_systems[i].TP_electors > 0) {
                full_uncap_systems++;
            }
        }

        // Get data from year file, and return USA array
        int file_loaded = 0; // Variable to track file loading
        while (1) {
            fflush(stdin);
            input_year = 0;
            printf("Which year do you want to investigate? ");
            if(scanf("%d", &input_year) !=1) {
                printf("Invalid input. Please enter a valid year.\n\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                continue;
            }
            printf("\n");
            // If year already simulated and the comparison is full, user try again
            if (input_year == cap_systems[0].year && full_cap_systems == NO_SYSTEMS && full_uncap_systems == NO_SYSTEMS) {
                printf("The year %d has just been simulated.\n\n", input_year);
                continue;
            }
            // Check if the year is part of the files
            file_loaded = ScanData_TXT(input_year, USA);
            if (!file_loaded) {
                printf("Invalid year or file not found. Please try again.\n\n");
            } else {
                break;
            }
        }

        // Insert the year in the cmp system array, empty arrays if different year is entered
        if (cap_systems[0].year != input_year) {
            memset(cap_systems, 0, NO_SYSTEMS * sizeof(cmp));
            memset(uncap_systems, 0, NO_SYSTEMS * sizeof(cmp));
            full_cap_systems = 0;
            full_uncap_systems = 0;
            cap_systems[0].year = input_year;
        } else {
            cap_systems[0].year = input_year;
        }

        // Allocate memory for the array candidate_list
        candidates* candidate_list = malloc(CANDIDATES * sizeof(candidates));
        if (candidate_list == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        ScanCandidatesTXT(input_year ,candidate_list);

        // Uncapping the US Electoral College
        while (1) {
            fflush(stdin);
            printf("Would you like to uncap the Electoral College (EC) from its current 538 electors? (yes/no): ");

            // Checking for faulty input
            if (fgets(wyoming_rule_true, sizeof(wyoming_rule_true), stdin) == NULL) {
                printf("Error reading input. Please try again.\n");
                continue;
            }

            // Remove trailing newline character, if present
            wyoming_rule_true[strcspn(wyoming_rule_true, "\n")] = '\0';

            // Convert to lowercase for case-insensitive comparison
            for (int i = 0; wyoming_rule_true[i]; i++) {
                wyoming_rule_true[i] = tolower(wyoming_rule_true[i]);
            }

            // Checking if input is valid, as well if its possible to uncap the system for that specific year
            if(strcmp(wyoming_rule_true, "yes") == 0 || strcmp(wyoming_rule_true, "y") == 0) {
                if(full_uncap_systems == NO_SYSTEMS) {
                    printf("Your choice '%s' has already been simulated for all systems.\n", wyoming_rule_true);
                    continue;
                }else {
                    wyoming_rule(USA, cap_systems, 0);
                    uncapped = 1;
                    break;
                }
            } else if (strcmp(wyoming_rule_true, "no") == 0 || strcmp(wyoming_rule_true, "n") == 0) {
                if (full_cap_systems == NO_SYSTEMS) {
                    printf("Your choice '%s' has already been simulated for all systems.\n", wyoming_rule_true);
                    continue;
                }else {
                    break;
                }
            } else {
                printf("Invalid input. Please try again.\n\n");
            }
        }
        printf("\n");
        // Disbanding all states, so the entire vote is only between the people instead of each state
        do {
            printf("Would you like to disband all states in the US? (yes/no): ");
            scanf("%s", &abolish_states_true);
            printf("\n");
            // Clear the input buffer to handle invalid input
            while (getchar() != '\n');
            for (int i = 0; abolish_states_true[i] != '\0'; i++) {
                abolish_states_true[i] = tolower(abolish_states_true[i]);
            }
        } while (strcmp(abolish_states_true,"yes") != 0 && strcmp(abolish_states_true,"no") != 0 && strcmp(abolish_states_true,"y") != 0 && strcmp(abolish_states_true,"n") != 0);
        if (strcmp(abolish_states_true,"yes") == 0 || strcmp(abolish_states_true,"y") == 0) {
            abolish_states(USA);
            states_abolished = 1;
        }

        // Determine the winner
        char* result = Winner_of_election(USA, candidate_list, cap_systems, uncap_systems, system, uncapped, states_abolished, 0);
        printf("With the Electoral college (%s system), the winner was the %s.\n\n", system, result);

        // User Choose a new system
        printf("Choose a new system: STV, PLPR, BC, Custom or All\nor 'INFO' for further information: ");
        scanf("%s", system);
        for (int i = 0; system[i] != '\0'; i++) {
            system[i] = toupper(system[i]);
        }
        // Determine the winner
        result = Winner_of_election(USA, candidate_list, cap_systems, uncap_systems, system, uncapped, states_abolished, 0);
        if (strcmp(result, "Custom Done") != 0 && strcmp(result, "All systems") != 0) {
            printf("The winner was the %s, with the %s system.\n\n", result, system);
        }

        if (strcmp(result, "All systems") == 0) {
            // Nothing
        } else {
            // Compare the tested systems
            if (strcmp(result, "Custom Done") != 0) {
                if (!states_abolished) {
                    Compare_table(USA, candidate_list, cap_systems, uncap_systems, 0);
                }
            } else {
                // Reset the 2 arrays if custom is activated
                memset(cap_systems, 0, NO_SYSTEMS * sizeof(cmp));
                memset(uncap_systems, 0, NO_SYSTEMS * sizeof(cmp));
            }
            // Ask the user if they wish to see the weight of their vote
            char decide[4];
            if (abolish_states_true[0] == 'n') {
                do {
                    printf("Do you wish to see the weight of an electors vote? (yes/no): ");
                    scanf("%s", &decide);
                    printf("\n");
                    while (getchar() != '\n');
                    for (int i = 0; decide[i] != '\0'; i++) {
                        decide[i] = tolower(decide[i]);
                    }
                }while (strcmp(decide,"yes") != 0 && strcmp(decide,"no") != 0 && strcmp(decide,"y") != 0 && strcmp(decide,"n") != 0);
                // Exit the loop if the user chooses 'yes'
                if (strcmp(decide,"yes") == 0 || strcmp(decide,"y") == 0) {
                    weight(USA,&first_run);
                    first_run = 1;
                }
            }
        }
        // Free Arrays
        free(USA);
        free(candidate_list);

        // Ask the user if they want to end the program
        char choice[4];
        do {
            printf("Do you want to end the program? (yes/no): ");
            scanf("%s", &choice);
            printf("\n");

            // Clear the input buffer to handle invalid input
            while (getchar() != '\n');
            for (int i = 0; choice[i] != '\0'; i++) {
                choice[i] = tolower(choice[i]);
            }
        } while (strcmp(choice,"yes") != 0 && strcmp(choice,"no") != 0 && strcmp(choice,"y") != 0 && strcmp(choice,"n") != 0);
        // Exit the loop if the user chooses 'yes'
        if (strcmp(choice,"yes") == 0 || strcmp(choice,"y") == 0) {
            printf("Exiting the program. Goodbye!\n");
            sleep(2);
            break;
        }
    }
    free(cap_systems);
    free(uncap_systems);
    return 0;
}