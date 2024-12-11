#include "../connecter.h"
void copy_systems_names(cmp* cap_systems, cmp* uncap_systems) {
    for (int i = 0; i < NO_SYSTEMS; i++) {
        if (strlen(cap_systems[i].system_name) == 0) {
            strcpy(cap_systems[i].system_name, uncap_systems[i].system_name);
        } else if (strlen(uncap_systems[i].system_name) == 0) {
            strcpy(uncap_systems[i].system_name, cap_systems[i].system_name);
        }
    }
}