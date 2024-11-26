//
// Created by nikol on 26-11-2024.
//
#include "connecter.h"

void list_available_files(const char* directory) {
    //open folder with data
    struct dirent *entry;
    DIR *dir = opendir(directory);

    //if no folder can be found, no data can be shown
    if (dir == NULL) {
        printf("Could not find data: %s\n", directory);
        return;
    }

    //print available data in form of years
    printf("Available years: ");
    int comma = 1;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            //variables defining parts of file names which will be cut
            char* file_name_remove = "US_Election_";
            char* file_type_remove = ".txt";
            //if statement which compares file names, with former variables
            if (strncmp(entry->d_name, file_name_remove, strlen(file_name_remove)) == 0 && strstr(entry->d_name, file_type_remove) != NULL) {
                //extracting the year out of the file name, and printing the year
                char year[5];
                strncpy(year, entry->d_name + strlen(file_name_remove), 4);
                year[4] = '\0';

                if (!comma) {
                    printf(", ");
                }
                printf("%s", year);
                comma = 0;
            }
        }
    }
    printf("\n");
    closedir(dir);
}


