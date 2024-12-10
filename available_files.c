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
    printf("Available years (1 = example Custom file): \n");
    int comma = 1;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            //variables defining parts of file names which will be cut
            char* file_name_remove = "US_Election_";
            char* file_type_remove = ".txt";
            //if statement which compares file names, with former variables
            if (strncmp(entry->d_name, file_name_remove, strlen(file_name_remove)) == 0 && strstr(entry->d_name, file_type_remove) != NULL) {
                //calculating length of year
                size_t year_start = strlen(file_name_remove); // Start of the year (length of "US_Election_")
                size_t year_end = strstr(entry->d_name, file_type_remove) - entry->d_name; // Position of ".txt"
                size_t year_length = year_end - year_start; // Length of the year substring

                //extracting the year out of the file name, and printing the year
                char year[year_length+1];
                strncpy(year, entry->d_name + year_start, year_length);
                year[year_length] = '\0';

                if (!comma) {
                    printf(", ");
                }
                printf("%s", year);
                comma = 0;
            }
        }
    }
    printf("\n\n");
    closedir(dir);
}


