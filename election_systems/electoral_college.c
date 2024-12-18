#include "../connecter.h"
// Simulates the standard US Electoral system
char* electoral_college(states* USA, cmp* cap_systems, cmp* uncap_systems, int uncapped, int states_abolished) {
    int electors = 0, democrats = 0, republicans = 0, third_party = 0;
    // Distribute the electors based on the highest percentage in the state
    for (int i = 0; i < STATES; i++) {
        electors += USA[i].electors;
        if (USA[i].dem_votes > USA[i].third_votes  && USA[i].dem_votes > USA[i].rep_votes) {
            if (strcmp(USA[i].stateName,"Maine") == 0 && cap_systems[0].year == 2016) {
                democrats += USA[i].electors;
                democrats--;
                republicans++;
            }else {
                democrats += USA[i].electors;
            }
        } else if (USA[i].rep_votes > USA[i].third_votes) {
            if (strcmp(USA[i].stateName,"Nebraska") == 0 && cap_systems[0].year == 2008) {
                republicans += USA[i].electors;
                republicans--;
                democrats ++;
            }else {
                republicans += USA[i].electors;
            }
        } else {
            third_party += USA[i].electors;
        }
    }
    // Print the electors for each party
    printf("\nDemocrat electors: %d\n", democrats);
    printf("Republican electors: %d\n", republicans);
    printf("Third party electors: %d\n\n", third_party);
    // Save the electors in the cmp systems array
    if (!states_abolished) {
        if (uncapped) {
            strcpy(uncap_systems[0].system_name, "EC");
            uncap_systems[0].DEM_electors = democrats;
            uncap_systems[0].REP_electors = republicans;
            uncap_systems[0].TP_electors = third_party;
        } else {
            strcpy(cap_systems[0].system_name, "EC");
            cap_systems[0].DEM_electors = democrats;
            cap_systems[0].REP_electors = republicans;
            cap_systems[0].TP_electors = third_party;
        }
        // Copy system names from cap to uncap, and opposite
        copy_systems_names(cap_systems, uncap_systems);
    }
    // Return winning party
    if (democrats > (electors/2)+1) {
        return "Democrats";
    } else if (republicans > (electors/2)+1){
        return "Republicans";
    } else {
        return "Third_party";
    }
}