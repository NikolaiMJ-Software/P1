#include "../connecter.h"

void Compare_table(cmp* e_systems, int counter_CMP) {
    printf("\nYear: %d\n", e_systems[0].year);
    for (int i = 0; i <= counter_CMP; i++) {
        printf("Election system: %s\n", e_systems[i].system_name);
        printf("Democrat electors: %d\n", e_systems[i].DEM_electors);
        printf("Republican electors: %d\n", e_systems[i].REP_electors);
        printf("Third party electors: %d\n", e_systems[i].TP_electors);
        printf("\n");
    }
    /*
    printf("\nYear: %d %13.s %4.s %4.s\n", );
    printf("Democrat electors: %6.d %7.d %6.d\n", PLPR_dem, STV_dem, BC_dem);
    printf("Republican electors: %4.d %7.d %6.d\n", PLPR_rep, STV_rep, BC_rep);
    printf("Third party electors: %3.d %7.d %6.d\n\n", PLPR_tp, STV_tp, BC_tp);
    */
}