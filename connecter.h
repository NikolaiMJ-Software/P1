#ifndef SCAN_DATA_TXT_H
#define SCAN_DATA_TXT_H
#define NAME_LGT 14
#define STATES 50

//creation of the states struct
typedef struct states {
    char stateName[NAME_LGT];
    int electors;
    double democrats;
    double republicans;
    int population;
}states;

void ScanData_TXT(int input_year, states* USA);
char* Winner_of_election(states* USA, char* system);
char* electoral_college(states* USA);
char* PLPR(states* USA);
char* STV(states* USA);
char* BC(states* USA);

#endif //SCAN_DATA_TXT_H