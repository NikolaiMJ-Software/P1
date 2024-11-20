//
// Created by 02fre on 20-11-2024.
//

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
void ScanData_TXT(int input_year);
char Winner_of_election();



#endif //SCAN_DATA_TXT_H
