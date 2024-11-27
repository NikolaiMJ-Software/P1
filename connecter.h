#ifndef SCAN_DATA_TXT_H
#define SCAN_DATA_TXT_H
#define NAME_LGT 30
#define STATES 51
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>

//creation of the states struct
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

// Enum for allowed party values
typedef enum {
    REPUBLICAN = 0,
    DEMOCRATIC = 1,
    THIRD_PARTY = 2
} Party;

// Enum for allowed candidacy values
typedef enum {
    PRESIDENT = 0,
    VICE_PRESIDENT = 1,
    BOTH = 2
} Candidacy;

//Creation of the candidates struct
typedef struct candidates {
    Party party;
    char name[NAME_LGT];
    Candidacy candidacy;
}candidates;

int ScanData_TXT(int input_year, states* USA);
char* Winner_of_election(states* USA, char* system, int input_year);
char* electoral_college(states* USA, int year);
char* PLPR(states* USA);
char* STV(states* USA);
char* BC(states* USA);
void monte_carlo(states* USA, int state, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes);
void wyoming_rule(int input_year,states* USA);
void list_available_files(const char* directory);

#endif //SCAN_DATA_TXT_H