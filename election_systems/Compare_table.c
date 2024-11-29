#include "../connecter.h";
#include <stdio.h>


char* PLPR(states* USA, int* democrats, int* republicans, int* third_party);
char* STV(states* USA, int* dem_electors, int* rep_electors, int* tp_electors);
char* BC(states* USA, int* allocated_dem_electors, int* allocated_rep_electors, int* allocated_tp_electors);


char Compare_table(states* USA) {
    int PLPR_dem, PLPR_rep, PLPR_tp;
    int STV_dem, STV_rep, STV_tp;
    int BC_dem, BC_rep, BC_tp;

    PLPR(USA, &PLPR_dem, &PLPR_rep, &PLPR_tp);
    STV(USA, &STV_dem, &STV_rep, &STV_tp);
    BC(USA, &BC_dem, &BC_rep, &BC_tp);



    printf("\n                      PLPR    STV     BC\n");
    printf("Democrat electors: %6.d %7.d %7.d\n", PLPR_dem, STV_dem, BC_dem);
    printf("Republican electors: %4.d %7.d %7.d\n", PLPR_rep, STV_rep, BC_rep);
    printf("Third party electors: %3.d %7.d %7.d\n", PLPR_tp, STV_tp, BC_tp);

return 0;
}