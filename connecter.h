#ifndef SCAN_DATA_TXT_H
#define SCAN_DATA_TXT_H
#define NAME_LGT 30
#define STATES 51
#define CANDIDATES 25
#define NO_SYSTEMS 4
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>

// Creation of the states struct
typedef struct states {
    char stateName[NAME_LGT];
    int electors;
    double democrats;
    double republicans;
    double third_party;
    int population;
    int dem_votes;
    int rep_votes;
    int third_votes;
}states;

// Creation of the comparison struct
typedef struct cmp {
    char system_name[NAME_LGT];
    int DEM_electors;
    int REP_electors;
    int TP_electors;
    int year;
}cmp;

// Enum for allowed party values
typedef enum {
    Republican,
    Democratic,
    Third_Party
} Party;

// Enum for allowed candidacy values
typedef enum {
    President,
    Vice_President,
    Both
} Candidacy;

//Creation of the candidates struct
typedef struct candidates {
    Party party;
    char name[NAME_LGT];
    Candidacy candidacy;
    int p_popularity_percentage;
    int vp_popularity_percentage;
    int p_votes;
    int vp_votes;
}candidates;

//prototypes for all functions connecting them to the main and other c files
int ScanData_TXT(int input_year, states* USA);
char* Winner_of_election(states* USA, candidates* candidate_list, cmp* cap_systems, cmp* uncap_systems, char* system, int input_year, int uncapped, int states_abolished);
char* electoral_college(states* USA, cmp* cap_systems, cmp* uncap_systems, int year, int uncapped, int states_abolished);
char* PLPR(states* USA, cmp* cap_systems, cmp* uncap_systems, int counter_cap, int counter_uncap, int uncapped, int states_abolished);
char* STV(states* USA, cmp* cap_systems, cmp* uncap_systems, int activate_progress, int counter_cap, int counter_uncap, int uncapped, int states_abolished);
char* BC(states* USA, cmp* cap_systems, cmp* uncap_systems, int activate_progress, int counter_cap, int counter_uncap, int uncapped, int states_abolished);
void Compare_table(cmp* cap_systems, cmp* uncap_systems);
void monte_carlo(states* USA, int state, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes);
void wyoming_rule(int input_year,states* USA);
void list_available_files(const char* directory);
int ScanCandidatesTXT(int input_year, candidates* candidate_list);
void parameters(states* state, candidates* candidate_list, int year);
void weight(states* USA);
void abolish_states(states* USA);
void printUSA();


#endif //SCAN_DATA_TXT_H