#include "connecter.h"

char* Winner_of_election(states* USA, char* system, int input_year) {
    int ORIG_dem, ORIG_rep, ORIG_tp;
    int PLPR_dem, PLPR_rep, PLPR_tp;
    int STV_dem, STV_rep, STV_tp;
    int BC_dem, BC_rep, BC_tp;

    while(true) {
        if (strcmp(system, "original") == 0) {
            return electoral_college(USA, input_year);
        } else if (strcmp(system, "STV") == 0) {
            return STV(USA, 1);
        } else if (strcmp(system, "PLPR") == 0) {
            return PLPR(USA);
        } else if (strcmp(system, "BC") == 0) {
            return BC(USA, 1);
        } else {
            printf("The chosen election system is not in the database, try again.\n");
            printf("Chose a new system: STV, PLPR, BC or compare the systems using 'CMP':\n");
            scanf("%s", system);
            for (int i = 0; system[i] != '\0'; i++) {
                system[i] = toupper(system[i]);
            }
        }
    }
}