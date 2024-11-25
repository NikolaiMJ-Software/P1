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

int ScanData_TXT(int input_year, states* USA);
char* Winner_of_election(states* USA, char* system);
char* electoral_college(states* USA);
char* PLPR(states* USA);
char* STV(states* USA);
char* BC(states* USA);
void monte_carlo(int old_DEM, int old_REP, int old_third, int choice, int* new_DEM_votes, int* new_REP_votes, int* new_TP_votes);
void wyoming_rule(int input_year,states* USA);

#endif //SCAN_DATA_TXT_H