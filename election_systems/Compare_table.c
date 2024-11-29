#include "../connecter.h"

void Compare_table(states* USA) {
    int PLPR_dem, PLPR_rep, PLPR_tp;
    int STV_dem, STV_rep, STV_tp;
    int BC_dem, BC_rep, BC_tp;

    printf("PLPR\n");
    PLPR(USA, &PLPR_dem, &PLPR_rep, &PLPR_tp);
    printf("STV\n");
    STV(USA, &STV_dem, &STV_rep, &STV_tp, 0);
    printf("BC\n");
    BC(USA, &BC_dem, &BC_rep, &BC_tp, 0);

    printf("\n                      PLPR    STV     BC\n");
    printf("Democrat electors: %6.d %7.d %7.d\n", PLPR_dem, STV_dem, BC_dem);
    printf("Republican electors: %4.d %7.d %7.d\n", PLPR_rep, STV_rep, BC_rep);
    printf("Third party electors: %3.d %7.d %7.d\n\n", PLPR_tp, STV_tp, BC_tp);
}