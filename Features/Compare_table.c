#include "../connecter.h"

void cap_names(cmp* e_systems, int counter_cap);
void uncap_names(cmp* uncap_systems, int counter_uncap);
void cap_DEM(cmp* e_systems, int counter_cap);
void uncap_DEM(cmp* uncap_systems, int counter_uncap);
void cap_REP(cmp* e_systems, int counter_cap);
void uncap_REP(cmp* uncap_systems, int counter_uncap);
void cap_TP(cmp* e_systems, int counter_cap);
void uncap_TP(cmp* uncap_systems, int counter_uncap);

void Compare_table(cmp* e_systems, cmp* uncap_systems) {
    for(int i = 0; i < NO_SYSTEMS; i++) {
        if (strlen(e_systems[i].system_name) == 0) {
            strcpy(e_systems[i].system_name, uncap_systems[i].system_name);
        } else if (strlen(uncap_systems[i].system_name) == 0) {
                strcpy(uncap_systems[i].system_name, e_systems[i].system_name);
        }
    }
    int counter_cap = 0, counter_uncap = 0;

    // Normal systems
    for (int i = 0; i < NO_SYSTEMS; i++) {
        if (e_systems[i].DEM_electors != 0 && e_systems[i].REP_electors != 0 && e_systems[i].TP_electors != 0) {
            counter_cap = i;
        }
    }
    // Uncap systems
    for (int i = 0; i < NO_SYSTEMS; i++) {
        if (uncap_systems[i].DEM_electors != 0 && uncap_systems[i].REP_electors != 0 && uncap_systems[i].TP_electors != 0) {
            counter_uncap = i;
        }
    }
    printf("\n%d %d\n", counter_cap, counter_uncap);

    printf("\n-----------------------------------Comparison table-----------------------------------\n");
    // 1 line
    cap_names(e_systems, counter_cap);
    uncap_names(uncap_systems, counter_uncap);
    // 2 line
    cap_DEM(e_systems, counter_cap);
    uncap_DEM(uncap_systems, counter_uncap);
    // 3 line
    cap_REP(e_systems, counter_cap);
    uncap_REP(uncap_systems, counter_uncap);
    // 4 line
    cap_TP(e_systems, counter_cap);
    uncap_TP(uncap_systems, counter_uncap);
}

// Print spaces between systems name in comparison table, based on the simulated order. If the system has not been compare yet, it will not be printed.
void cap_names(cmp* e_systems, int counter_cap) {
    // Empty cap_systems
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Year: %d %34s", e_systems[0].year, empty);
    } else
    // Order BC(1), STV(2), PLPR(3)
    if (strcmp(e_systems[1].system_name, "BC") == 0 && counter_cap >= 1) {
        if (strcmp(e_systems[2].system_name, "STV") == 0 && counter_cap >= 2) {
            if (e_systems[3].DEM_electors != 0 && e_systems[3].REP_electors != 0 && e_systems[3].TP_electors != 0) {
                printf("Year: %d %13s %6s %7s %7s %14s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, e_systems[3].system_name, empty);
            } else {
                // Order BC(1), STV(2)
                printf("Year: %d %13s %6s %7s %22s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, empty);
            }
        // Order BC(1), PLPR(2), STV(3)
        } else if (strcmp(e_systems[2].system_name, "PLPR") == 0 && counter_cap >= 2) {
            if (e_systems[3].DEM_electors != 0 && e_systems[3].REP_electors != 0 && e_systems[3].TP_electors != 0) {
                printf("Year: %d %13s %6s %8s %5s %15s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, e_systems[3].system_name, empty);
            } else {
                // Order BC(1), PLPR(2)
                printf("Year: %d %13s %6s %8s %21s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, empty);
            }
        } else {
            // Order BC(1)
            printf("Year: %d %13s %6s %30s", e_systems[0].year,
                e_systems[0].system_name, e_systems[1].system_name, empty);
        }
    // Order STV(1), BC(2), PLPR(3)
    } else if (strcmp(e_systems[1].system_name, "STV") == 0 && counter_cap >= 1) {
        if (strcmp(e_systems[2].system_name, "BC") == 0 && counter_cap >= 2) {
            if (e_systems[3].DEM_electors != 0 && e_systems[3].REP_electors != 0 && e_systems[3].TP_electors != 0) {
                printf("Year: %d %13s %7s %5s %8s %14s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, e_systems[3].system_name, empty);
            } else {
                // Order STV(1), BC(2)
                printf("Year: %d %13s %7s %5s %23s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, empty);
            }
        // Order STV(1), PLPR(2), BC(3)
        } else if (strcmp(e_systems[2].system_name, "PLPR") == 0 && counter_cap >= 2) {
            if (e_systems[3].DEM_electors != 0 && e_systems[3].REP_electors != 0 && e_systems[3].TP_electors != 0) {
                printf("Year: %d %13s %7s %7s %4s %16s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, e_systems[3].system_name, empty);
            } else {
                // Order STV(1), PLPR(2)
                printf("Year: %d %13s %7s %7s %21s", e_systems[0].year,
            e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, empty);
            }
        } else {
            // Order STV(1)
            printf("Year: %d %13s %7s %29s", e_systems[0].year,
                e_systems[0].system_name, e_systems[1].system_name, empty);
        }
    // Order PLPR(1), BC(2), STV(3)
    } else if (strcmp(e_systems[1].system_name, "PLPR") == 0 && counter_cap >= 1) {
        if (strcmp(e_systems[2].system_name, "BC") == 0 && counter_cap >= 2) {
            if (e_systems[3].DEM_electors != 0 && e_systems[3].REP_electors != 0 && e_systems[3].TP_electors != 0) {
                printf("Year: %d %13s %8s %4s %7s %15s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, e_systems[3].system_name, empty);
            } else {
                // Order PLPR(1), BC(2)
                printf("Year: %d %13s %8s %4s %23s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, empty);
            }
        // Order PLPR(1), STV(2), BC(3)
        } else if (strcmp(e_systems[2].system_name, "STV") == 0 && counter_cap >= 2) {
            if (e_systems[3].DEM_electors != 0 && e_systems[3].REP_electors != 0 && e_systems[3].TP_electors != 0) {
                printf("Year: %d %13s %8s %5s %5s %16s", e_systems[0].year,
                    e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, e_systems[3].system_name, empty);
            } else {
                // Order PLPR(1), STV(2)
                printf("Year: %d %13s %8s %5s %22s", e_systems[0].year,
            e_systems[0].system_name, e_systems[1].system_name, e_systems[2].system_name, empty);
            }
        } else {
            // Order PLPR(1)
            printf("Year: %d %13s %8s %28s", e_systems[0].year,
                e_systems[0].system_name, e_systems[1].system_name, empty);
        }
    }
}

void uncap_names(cmp* uncap_systems, int counter_uncap) {
    // Empty cap_systems
    if (counter_uncap == 0) {
        // Print nothing
        printf("\n");
    } else
    // Order BC(1), STV(2), PLPR(3)
    if (strcmp(uncap_systems[1].system_name, "BC") == 0 && counter_uncap >= 1) {
        if (strcmp(uncap_systems[2].system_name, "STV") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%s %6s %7s %7s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order BC(1), STV(2)
                printf("%13s %6s %7s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        // Order BC(1), PLPR(2), STV(3)
        } else if (strcmp(uncap_systems[2].system_name, "PLPR") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%13s %6s %8s %5s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order BC(1), PLPR(2)
                printf("%13s %6s %8s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        } else {
            // Order BC(1)
            printf("%13s %6s\n",
                uncap_systems[0].system_name, uncap_systems[1].system_name);
        }
    // Order STV(1), BC(2), PLPR(3)
    } else if (strcmp(uncap_systems[1].system_name, "STV") == 0 && counter_uncap >= 1) {
        if (strcmp(uncap_systems[2].system_name, "BC") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%13s %7s %5s %8s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order STV(1), BC(2)
                printf("%13s %7s %5s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        // Order STV(1), PLPR(2), BC(3)
        } else if (strcmp(uncap_systems[2].system_name, "PLPR") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%13s %7s %7s %4s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order STV(1), PLPR(2)
                printf("%13s %7s %7s\n",
            uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        } else {
            // Order STV(1)
            printf("%13s %7s\n",
                uncap_systems[0].system_name, uncap_systems[1].system_name);
        }
    // Order PLPR(1), BC(2), STV(3)
    } else if (strcmp(uncap_systems[1].system_name, "PLPR") == 0 && counter_uncap >= 1) {
        if (strcmp(uncap_systems[2].system_name, "BC") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%13s %8s %4s %7s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order PLPR(1), BC(2)
                printf("%13s %8s %4s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        // Order PLPR(1), STV(2), BC(3)
        } else if (strcmp(uncap_systems[2].system_name, "STV") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%13s %8s %5s %5s\n",
                    uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order PLPR(1), STV(2)
                printf("%13s %8s %5s\n",
            uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        } else {
            // Order PLPR(1)
            printf("%13s %8s\n",
                uncap_systems[0].system_name, uncap_systems[1].system_name);
        }
    }
}

void cap_DEM(cmp* e_systems, int counter_cap) {
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Democrat electors: %31s", empty);
    } else if (counter_cap == 1) {
        printf("Democrat electors: %6d %6d %17s",
               e_systems[0].DEM_electors, e_systems[1].DEM_electors, empty);
    } else if (counter_cap == 2) {
        printf("Democrat electors: %6d %6d %6d %10s",
               e_systems[0].DEM_electors, e_systems[1].DEM_electors, e_systems[2].DEM_electors, empty);
    } else if (counter_cap == 3) {
        printf("Democrat electors: %6d %6d %6d %6d %3s",
               e_systems[0].DEM_electors, e_systems[1].DEM_electors, e_systems[2].DEM_electors, e_systems[3].DEM_electors, empty);
    }
}
void uncap_DEM(cmp* uncap_systems, int counter_uncap) {
    if (counter_uncap == 0) {
        printf("\n");
    } else if (counter_uncap == 1) {
        printf("Uncapped %6d %6d\n",
               uncap_systems[0].DEM_electors, uncap_systems[1].DEM_electors);
    } else if (counter_uncap == 2) {
        printf("Uncapped %6d %6d %6d\n",
               uncap_systems[0].DEM_electors, uncap_systems[1].DEM_electors, uncap_systems[2].DEM_electors);
    } else if (counter_uncap == 3) {
        printf("Uncapped %6d %6d %6d %6d\n",
               uncap_systems[0].DEM_electors, uncap_systems[1].DEM_electors, uncap_systems[2].DEM_electors, uncap_systems[3].DEM_electors);
    }
}
void cap_REP(cmp* e_systems, int counter_cap) {
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Republican electors: %29s", empty);
    } else if (counter_cap == 1) {
        printf("Republican electors: %4d %6d %17s",
               e_systems[0].REP_electors, e_systems[1].REP_electors, empty);
    } else if (counter_cap == 2) {
        printf("Republican electors: %4d %6d %6d %10s",
               e_systems[0].REP_electors, e_systems[1].REP_electors, e_systems[2].REP_electors, empty);
    } else if (counter_cap == 3) {
        printf("Republican electors: %4d %6d %6d %6d %3s",
               e_systems[0].REP_electors, e_systems[1].REP_electors, e_systems[2].REP_electors, e_systems[3].REP_electors, empty);
    }
}
void uncap_REP(cmp* uncap_systems, int counter_uncap) {
    if (counter_uncap == 0) {
        printf("\n");
    } else if (counter_uncap == 1) {
        printf("-------> %6d %6d\n",
               uncap_systems[0].REP_electors, uncap_systems[1].REP_electors);
    } else if (counter_uncap == 2) {
        printf("-------> %6d %6d %6d\n",
               uncap_systems[0].REP_electors, uncap_systems[1].REP_electors, uncap_systems[2].REP_electors);
    } else if (counter_uncap == 3) {
        printf("-------> %6d %6d %6d %6d\n",
               uncap_systems[0].REP_electors, uncap_systems[1].REP_electors, uncap_systems[2].REP_electors, uncap_systems[3].REP_electors);
    }
}
void cap_TP(cmp* e_systems, int counter_cap) {
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Third party electors: %40s", empty);
    } else if (counter_cap == 1) {
        printf("Third party electors: %3d %6d %29s",
               e_systems[0].TP_electors, e_systems[1].TP_electors, empty);
    } else if (counter_cap == 2) {
        printf("Third party electors: %3d %6d %6d %22s",
               e_systems[0].TP_electors, e_systems[1].TP_electors, e_systems[2].TP_electors, empty);
    } else if (counter_cap == 3) {
        printf("Third party electors: %3d %6d %6d %6d %15s",
               e_systems[0].TP_electors, e_systems[1].TP_electors, e_systems[2].TP_electors, e_systems[3].TP_electors, empty);
    }
}
void uncap_TP(cmp* uncap_systems, int counter_uncap) {
    if (counter_uncap == 0) {
        printf("\n\n");
    } else if (counter_uncap == 1) {
        printf("%3d %6d\n\n",
               uncap_systems[0].TP_electors, uncap_systems[1].TP_electors);
    } else if (counter_uncap == 2) {
        printf("%3d %6d %6d\n\n",
               uncap_systems[0].TP_electors, uncap_systems[1].TP_electors, uncap_systems[2].TP_electors);
    } else if (counter_uncap == 3) {
        printf("%3d %6d %6d %6d\n\n",
               uncap_systems[0].TP_electors, uncap_systems[1].TP_electors, uncap_systems[2].TP_electors, uncap_systems[3].TP_electors);
    }
}