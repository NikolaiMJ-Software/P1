#include "../connecter.h"

int spaces(cmp* e_systems, int counter_CMP);

void Compare_table(cmp* e_systems, int counter_CMP) {
    printf("\n----------------Comparison table----------------\n");
    if (counter_CMP == 1) {
        printf("Year: %d %13s %8s\n", e_systems[0].year,
            e_systems[0].system_name, e_systems[1].system_name);
        printf("Democrat electors: %6d %7d\n",
            e_systems[0].DEM_electors, e_systems[1].DEM_electors);
        printf("Republican electors: %4d %7d\n",
            e_systems[0].REP_electors, e_systems[1].REP_electors);
        printf("Third party electors: %3d %7d\n\n",
            e_systems[0].TP_electors, e_systems[1].TP_electors);
    } else if (counter_CMP == 2) {
        printf("Year: %d %13s %9s %4s\n", e_systems[0].year,
            e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name);
        printf("Democrat electors: %6d %7d %6d\n",
            e_systems[0].DEM_electors, e_systems[1].DEM_electors, e_systems[2].DEM_electors);
        printf("Republican electors: %4d %7d %6d\n",
            e_systems[0].REP_electors, e_systems[1].REP_electors, e_systems[2].REP_electors);
        printf("Third party electors: %3d %7d %6d\n\n",
            e_systems[0].TP_electors, e_systems[1].TP_electors, e_systems[2].TP_electors);
    } else if (counter_CMP == 3) {
        printf("Year: %d %13s %9s %4s %4s\n", e_systems[0].year,
            e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, e_systems[3].system_name);
        printf("Democrat electors: %6d %7d %6d %6d\n",
            e_systems[0].DEM_electors, e_systems[1].DEM_electors, e_systems[2].DEM_electors, e_systems[3].DEM_electors);
        printf("Republican electors: %4d %7d %6d %6d\n",
            e_systems[0].REP_electors, e_systems[1].REP_electors, e_systems[2].REP_electors, e_systems[3].REP_electors);
        printf("Third party electors: %3d %7d %6d %6d\n\n",
            e_systems[0].TP_electors, e_systems[1].TP_electors, e_systems[2].TP_electors, e_systems[3].TP_electors);
    }
}

int spaces(cmp* e_systems, int counter_CMP) {
    if (strcmp(e_systems[1].system_name, "BC") == 0) {
        if (counter_CMP == 1){return 7;}
            if (strcmp(e_systems[2].system_name, "PLPR") == 0) {return 4;}
            if (strcmp(e_systems[2].system_name, "STV") == 0) {return 8;}

    }
    if (strcmp(e_systems[1].system_name, "STV") == 0) {return 8;}
    if (strcmp(e_systems[1].system_name, "PLPR") == 0) {return 9;}

}