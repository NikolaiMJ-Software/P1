#include "../connecter.h"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define WHITE "\033[37m"
void cap_names(cmp* cap_systems, int counter_cap);
void uncap_names(cmp* uncap_systems, int counter_uncap);
void line_DEM(cmp* cap_systems, cmp* uncap_systems, int counter_cap, int counter_uncap);
void line_REP(cmp* cap_systems, cmp* uncap_systems, int counter_cap, int counter_uncap);
void line_TP(cmp* cap_systems, cmp* uncap_systems, int counter_cap, int counter_uncap);
void missing_systems(states* USA, candidates* candidate_list, cmp* cap_systems, cmp* uncap_systems);
void assign_cmp_colors(cmp* cap_systems, cmp* uncap_systems);
// Run compare_tabel from main.c
void Compare_table(states* USA, candidates* candidate_list, cmp* cap_systems, cmp* uncap_systems, int all_systems) {
    // If all systems is true the missing system will be calculated and added to the compare table
    if (all_systems) {
        missing_systems(USA, candidate_list, cap_systems, uncap_systems);
    }
    // Find how many systems is already simulated for cap and uncap
    int counter_cap = 0, counter_uncap = 0;
    for (int i = 0; i < NO_SYSTEMS; i++) {
        // Normal systems
        if (cap_systems[i].DEM_electors != 0 && cap_systems[i].REP_electors != 0 && cap_systems[i].TP_electors != 0) {
            counter_cap = i;
        }
        // Uncap systems
        if (uncap_systems[i].DEM_electors != 0 && uncap_systems[i].REP_electors != 0 && uncap_systems[i].TP_electors != 0) {
            counter_uncap = i;
        }
    }
    // Add colors to the winner of each system
    assign_cmp_colors(cap_systems, uncap_systems);
    // Print the Comparison table
    // Line: 0
    printf("\n-----------------------------------Comparison table-----------------------------------\n");
    // Line: 1
    cap_names(cap_systems, counter_cap);
    uncap_names(uncap_systems, counter_uncap);
    // Line: 2
    line_DEM(cap_systems, uncap_systems, counter_cap, counter_uncap);
    // Line: 3
    line_REP(cap_systems, uncap_systems, counter_cap, counter_uncap);
    // Line: 4
    line_TP(cap_systems, uncap_systems, counter_cap, counter_uncap);
}
// Print spaces between systems name in comparison table, based on the simulated order. If the system has not been compare yet, it will not be printed.
void cap_names(cmp* cap_systems, int counter_cap) {
    // Add extra space to system when year is under 1000
    char year_scale[4] = {'\0'};
    if (cap_systems[0].year < 1000) {
        if(cap_systems[0].year < 100) {
            if (cap_systems[0].year < 10) {
                strcpy(year_scale, "   ");
            } else {
                strcpy(year_scale, "  ");
            }
        } else {
            strcpy(year_scale, " ");
        }
    }
    // Empty cap_systems
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Year: %d%s %51s", cap_systems[0].year, year_scale, empty);
    } else
    // Order BC(1), STV(2), PLPR(3)
    if (strcmp(cap_systems[1].system_name, "BC") == 0 && counter_cap >= 1) {
        if (strcmp(cap_systems[2].system_name, "STV") == 0 && counter_cap >= 2) {
            if (cap_systems[3].DEM_electors != 0 && cap_systems[3].REP_electors != 0 && cap_systems[3].TP_electors != 0) {
                printf("Year: %d%s %13s %6s %7s %7s %14s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, cap_systems[3].system_name, empty);
            } else {
                // Order BC(1), STV(2)
                printf("Year: %d%s %13s %6s %7s %22s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, empty);
            }
        // Order BC(1), PLPR(2), STV(3)
        } else if (strcmp(cap_systems[2].system_name, "PLPR") == 0 && counter_cap >= 2) {
            if (cap_systems[3].DEM_electors != 0 && cap_systems[3].REP_electors != 0 && cap_systems[3].TP_electors != 0) {
                printf("Year: %d%s %13s %6s %8s %5s %15s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, cap_systems[3].system_name, empty);
            } else {
                // Order BC(1), PLPR(2)
                printf("Year: %d%s %13s %6s %8s %21s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, empty);
            }
        } else {
            // Order BC(1)
            printf("Year: %d%s %13s %6s %30s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, empty);
        }
    // Order STV(1), BC(2), PLPR(3)
    } else if (strcmp(cap_systems[1].system_name, "STV") == 0 && counter_cap >= 1) {
        if (strcmp(cap_systems[2].system_name, "BC") == 0 && counter_cap >= 2) {
            if (cap_systems[3].DEM_electors != 0 && cap_systems[3].REP_electors != 0 && cap_systems[3].TP_electors != 0) {
                printf("Year: %d%s %13s %7s %5s %8s %14s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, cap_systems[3].system_name, empty);
            } else {
                // Order STV(1), BC(2)
                printf("Year: %d%s %13s %7s %5s %23s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, empty);
            }
        // Order STV(1), PLPR(2), BC(3)
        } else if (strcmp(cap_systems[2].system_name, "PLPR") == 0 && counter_cap >= 2) {
            if (cap_systems[3].DEM_electors != 0 && cap_systems[3].REP_electors != 0 && cap_systems[3].TP_electors != 0) {
                printf("Year: %d%s %13s %7s %7s %4s %16s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, cap_systems[3].system_name, empty);
            } else {
                // Order STV(1), PLPR(2)
                printf("Year: %d%s %13s %7s %7s %21s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, empty);
            }
        } else {
            // Order STV(1)
            printf("Year: %d%s %13s %7s %29s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, empty);
        }
    // Order PLPR(1), BC(2), STV(3)
    } else if (strcmp(cap_systems[1].system_name, "PLPR") == 0 && counter_cap >= 1) {
        if (strcmp(cap_systems[2].system_name, "BC") == 0 && counter_cap >= 2) {
            if (cap_systems[3].DEM_electors != 0 && cap_systems[3].REP_electors != 0 && cap_systems[3].TP_electors != 0) {
                printf("Year: %d%s %13s %8s %4s %7s %15s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, cap_systems[3].system_name, empty);
            } else {
                // Order PLPR(1), BC(2)
                printf("Year: %d%s %13s %8s %4s %23s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, empty);
            }
        // Order PLPR(1), STV(2), BC(3)
        } else if (strcmp(cap_systems[2].system_name, "STV") == 0 && counter_cap >= 2) {
            if (cap_systems[3].DEM_electors != 0 && cap_systems[3].REP_electors != 0 && cap_systems[3].TP_electors != 0) {
                printf("Year: %d%s %13s %8s %5s %5s %16s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, cap_systems[3].system_name, empty);
            } else {
                // Order PLPR(1), STV(2)
                printf("Year: %d%s %13s %8s %5s %22s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, cap_systems[2].system_name, empty);
            }
        } else {
            // Order PLPR(1)
            printf("Year: %d%s %13s %8s %28s", cap_systems[0].year, year_scale, cap_systems[0].system_name, cap_systems[1].system_name, empty);
        }
    }
}
// Print uncap_names
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
                printf("%s %6s %7s %7s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order BC(1), STV(2)
                printf("%s %6s %7s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        // Order BC(1), PLPR(2), STV(3)
        } else if (strcmp(uncap_systems[2].system_name, "PLPR") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%s %6s %8s %5s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order BC(1), PLPR(2)
                printf("%s %6s %8s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        } else {
            // Order BC(1)
            printf("%s %6s\n", uncap_systems[0].system_name, uncap_systems[1].system_name);
        }
    // Order STV(1), BC(2), PLPR(3)
    } else if (strcmp(uncap_systems[1].system_name, "STV") == 0 && counter_uncap >= 1) {
        if (strcmp(uncap_systems[2].system_name, "BC") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%s %7s %5s %8s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order STV(1), BC(2)
                printf("%s %7s %5s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        // Order STV(1), PLPR(2), BC(3)
        } else if (strcmp(uncap_systems[2].system_name, "PLPR") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%s %7s %7s %4s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order STV(1), PLPR(2)
                printf("%s %7s %7s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        } else {
            // Order STV(1)
            printf("%s %7s\n", uncap_systems[0].system_name, uncap_systems[1].system_name);
        }
    // Order PLPR(1), BC(2), STV(3)
    } else if (strcmp(uncap_systems[1].system_name, "PLPR") == 0 && counter_uncap >= 1) {
        if (strcmp(uncap_systems[2].system_name, "BC") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%s %8s %4s %7s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order PLPR(1), BC(2)
                printf("%s %8s %4s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        // Order PLPR(1), STV(2), BC(3)
        } else if (strcmp(uncap_systems[2].system_name, "STV") == 0 && counter_uncap >= 2) {
            if (uncap_systems[3].DEM_electors != 0 && uncap_systems[3].REP_electors != 0 && uncap_systems[3].TP_electors != 0) {
                printf("%s %8s %5s %5s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name, uncap_systems[3].system_name);
            } else {
                // Order PLPR(1), STV(2)
                printf("%s %8s %5s\n", uncap_systems[0].system_name, uncap_systems[1].system_name, uncap_systems[2].system_name);
            }
        } else {
            // Order PLPR(1)
            printf("%s %8s\n", uncap_systems[0].system_name, uncap_systems[1].system_name);
        }
    }
}
// Print of 2 line
void line_DEM(cmp* cap_systems, cmp* uncap_systems, int counter_cap, int counter_uncap) {
    // Cap DEM
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Democrat electors: %31s", empty);
    } else {
        printf("Democrat electors: ");
        for (int i = 0; i <= counter_cap; i++) {
            printf("%s%6d\033[0m ", cap_systems[i].DEM_color, cap_systems[i].DEM_electors);
        }
        if (counter_cap == 1) {
            printf("%17s", empty);
        } else if (counter_cap == 2) {
            printf("%10s", empty);
        } else if (counter_cap == 3) {
            printf("%3s", empty);
        }
    }
    // Uncap DEM
    if (counter_uncap == 0) {
        printf("\n");
    } else {
        printf("Uncapped ");
        for (int i = 0; i <= counter_uncap; i++) {
            printf("%s%6d\033[0m ", uncap_systems[i].DEM_color, uncap_systems[i].DEM_electors);
        }
        printf("\n");
    }
}
// Print of 3 line
void line_REP(cmp* cap_systems, cmp* uncap_systems, int counter_cap, int counter_uncap) {
    // Cap REP
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Republican electors: %29s", empty);
    } else {
        printf("Republican electors: %s%4d\033[0m ", cap_systems[0].REP_color, cap_systems[0].REP_electors);
        for (int i = 1; i <= counter_cap; i++) {
            printf("%s%6d\033[0m ", cap_systems[i].REP_color, cap_systems[i].REP_electors);
        }
        if (counter_cap == 1) {
            printf("%17s", empty);
        } else if (counter_cap == 2) {
            printf("%10s", empty);
        } else if (counter_cap == 3) {
            printf("%3s", empty);
        }
    }
    // Uncap REP
    if (counter_uncap == 0) {
        printf("\n");
    } else {
        printf("-------> ");
        for (int i = 0; i <= counter_uncap; i++) {
            printf("%s%6d\033[0m ", uncap_systems[i].REP_color, uncap_systems[i].REP_electors);
        }
        printf("\n");
    }
}
// Print of 4 line
void line_TP(cmp* cap_systems, cmp* uncap_systems, int counter_cap , int counter_uncap) {
    // Cap TP
    char empty[1] = {'\0'};
    if (counter_cap == 0) {
        printf("Third party electors: %37s", empty);
    } else {
        printf("Third party electors: %s%3d\033[0m ", cap_systems[0].TP_color, cap_systems[0].TP_electors);
        for (int i = 1; i <= counter_cap; i++) {
            printf("%s%6d\033[0m ", cap_systems[i].TP_color, cap_systems[i].TP_electors);
        }
        if (counter_cap == 1) {
            printf("%26s", empty);
        } else if (counter_cap == 2) {
            printf("%19s", empty);
        } else if (counter_cap == 3) {
            printf("%12s", empty);
        }
    }
    // Uncap TP
    if (counter_uncap == 0) {
        printf("\n\n");
    } else {
        for (int i = 0; i <= counter_uncap; i++) {
            printf("%s%6d\033[0m ", uncap_systems[i].TP_color, uncap_systems[i].TP_electors);
        }
        printf("\n\n");
    }
}
// Calculate missing systems
void missing_systems(states* USA, candidates* candidate_list, cmp* cap_systems, cmp* uncap_systems) {
    int uncapped = 0, states_abolished = 0;
    // Calculate cap EC if missing
    if (cap_systems[0].DEM_electors == 0 && cap_systems[0].REP_electors == 0 && cap_systems[0].TP_electors == 0) {
        // Rest data and call from txt again
        ScanData_TXT(cap_systems[0].year, USA);
        printf("Simulate election system (capped): %s\n", uncap_systems[0].system_name);
        electoral_college(USA, cap_systems, uncap_systems, uncapped, states_abolished);
    }
    // Calculate uncap EC if missing
    if (uncap_systems[0].DEM_electors == 0 && uncap_systems[0].REP_electors == 0 && uncap_systems[0].TP_electors == 0) {
        // Rest data and call from txt again
        ScanData_TXT(cap_systems[0].year, USA);
        // Uncap the electors
        wyoming_rule(USA, cap_systems, 1);
        uncapped = 1;
        printf("Simulate election system (uncapped): %s \n", uncap_systems[0].system_name);
        electoral_college(USA, cap_systems, uncap_systems, uncapped, states_abolished);
    }
    char system[5] = {'\0'};
    // Calculate capped systems
    for (int i = 1; i < NO_SYSTEMS; i++) {
        // Rest data and call from txt again
        ScanData_TXT(cap_systems[0].year, USA);
        // Locate and calculate missing systems in cap_systems array
        if (cap_systems[i].DEM_electors == 0 && cap_systems[i].REP_electors == 0 && cap_systems[i].TP_electors == 0) {
            // If cap system has a name and no electors, then simulate the system
            if (strlen(cap_systems[i].system_name) != 0) {
                strcpy(system, cap_systems[i].system_name);
                Winner_of_election(USA, candidate_list, cap_systems, uncap_systems, system, 0, states_abolished, 1);
            } else {
                // Predefined order BC, PLPR, STV
                const char* predefined_order[] = {"BC", "PLPR", "STV"};
                for (int j = 0; j < 3; j++) {
                    int found = 0;
                    for (int k = 1; k <= i; k++) {
                        // Check if a system name is already in the array
                        if (strcmp(cap_systems[k].system_name, predefined_order[j]) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    // If the system name is not found it will be simulated
                    if (!found) {
                        strcpy(system, predefined_order[j]);
                        printf("Simulate election system (capped): %s\n", predefined_order[j]);
                        Winner_of_election(USA, candidate_list, cap_systems, uncap_systems, system, 0, states_abolished, 1);
                    }
                }
            }
        }
    }
    // Calculate uncapped systems
    for (int i = 1; i < NO_SYSTEMS; i++) {
        // Rest data and call from txt again
        ScanData_TXT(cap_systems[0].year, USA);
        // Uncap the electors
        wyoming_rule(USA, cap_systems, 1);
        // Locate and calculate missing systems in uncap_systems array
        if (uncap_systems[i].DEM_electors == 0 && uncap_systems[i].REP_electors == 0 && uncap_systems[i].TP_electors == 0) {
            strcpy(system, cap_systems[i].system_name);
            printf("Simulate election system (uncapped): %s \n", uncap_systems[i].system_name);
            Winner_of_election(USA, candidate_list, cap_systems, uncap_systems, system, 1, states_abolished, 1);
        }
    }
}
// Add color to the winner of the simulated system
void assign_cmp_colors(cmp* cap_systems, cmp* uncap_systems) {
    for (int i = 0; i < NO_SYSTEMS; i++) {
        // Reset color to white
        strcpy(cap_systems[i].DEM_color, WHITE);
        strcpy(cap_systems[i].REP_color, WHITE);
        strcpy(cap_systems[i].TP_color, WHITE);
        // Assign colors to the winner for each system (cap_systems)
        if (cap_systems[i].DEM_electors > cap_systems[i].REP_electors && cap_systems[i].DEM_electors > cap_systems[i].TP_electors) {
            // Blue for DEM
            strcpy(cap_systems[i].DEM_color, BLUE);
        } else if (cap_systems[i].REP_electors > cap_systems[i].DEM_electors && cap_systems[i].REP_electors > cap_systems[i].TP_electors) {
            // Red for REP
            strcpy(cap_systems[i].REP_color, RED);
        } else if (cap_systems[i].TP_electors > cap_systems[i].DEM_electors && cap_systems[i].TP_electors > cap_systems[i].REP_electors) {
            // Green for TP
            strcpy(cap_systems[i].TP_color, GREEN);
        }

        // Reset color to white
        strcpy(uncap_systems[i].DEM_color, WHITE);
        strcpy(uncap_systems[i].REP_color, WHITE);
        strcpy(uncap_systems[i].TP_color, WHITE);
        // Assign colors to the winner for each system (uncap_systems)
        if (uncap_systems[i].DEM_electors > uncap_systems[i].REP_electors && uncap_systems[i].DEM_electors > uncap_systems[i].TP_electors) {
            // Blue for DEM
            strcpy(uncap_systems[i].DEM_color, BLUE);
        } else if (uncap_systems[i].REP_electors > uncap_systems[i].DEM_electors && uncap_systems[i].REP_electors > uncap_systems[i].TP_electors) {
            // Red for REP
            strcpy(uncap_systems[i].REP_color, RED);
        } else if (uncap_systems[i].TP_electors > uncap_systems[i].DEM_electors && uncap_systems[i].TP_electors > uncap_systems[i].REP_electors) {
            // Green for TP
            strcpy(uncap_systems[i].TP_color, GREEN);
        }
    }
}