#include "../connecter.h"
// Prototypes
Party string_to_party(const char* party);
Candidacy string_to_candidacy(const char* candidacy);

// Function to scan candidate txt files
int ScanCandidatesTXT(int input_year, candidates* candidate_list) {
    // Define file size
    char filename[50];
    // Choose specific file depending on input year
    snprintf(filename, sizeof(filename), "Candidates/Candidates_%d.txt", input_year);

    // Open file, and see if file exists
    FILE* inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    // Buffer
    char line[100];
    int i = 0;

    // Scanning data while loop
    while (fgets(line, sizeof(line), inputFile) && i<CANDIDATES) {
        char party_string[20], name_string[NAME_LGT], candidacy_string[20];
        int p_popularity = 0, vp_popularity = 0;

        // Scan data in form of chars, and return an error if not possible
        if (sscanf(line, "%19[^,], %49[^,], %19[^,], %d, %d", party_string, name_string, candidacy_string, &p_popularity, &vp_popularity) != 5) {
            printf("Error reading line: %s\n", line);
            fclose(inputFile);
            return 0;
        }

        // Cutting out space
        strtok(party_string, " ");
        strtok(candidacy_string, " ");

        // Converting party to 0, 1 or 2
        candidate_list[i].party = string_to_party(party_string);
        // Making name string valid, by inserting \0
        strncpy(candidate_list[i].name, name_string, NAME_LGT-1);
        candidate_list[i].name[NAME_LGT-1] = '\0';
        // Converting candidacy to 0, 1 or 2
        candidate_list[i].candidacy = string_to_candidacy(candidacy_string);
        // Storing popularity percentages
        candidate_list[i].p_popularity_percentage = p_popularity;
        candidate_list[i].vp_popularity_percentage = vp_popularity;
        candidate_list[i].p_votes = 0;
        candidate_list[i].vp_votes = 0;
        i++;
    }
    fclose(inputFile);
    return 1;
}

// Convert party to int function
Party string_to_party(const char* party) {
    if (strcmp(party, "Republican") == 0) {
        return Republican;
    } else if (strcmp(party, "Democratic") == 0) {
        return Democratic;
    } else if (strcmp(party, "Third_Party") == 0) {
        return Third_Party;
    } else {
        printf("Unknown party: %s\n", party);
        exit(EXIT_FAILURE);
    }
}

// Convert candidacy to in function
Candidacy string_to_candidacy(const char* candidacy) {
    if (strcmp(candidacy, "President") == 0) {
        return President;
    } else if (strcmp(candidacy, "Vice_President") == 0) {
        return Vice_President;
    } else if (strcmp(candidacy, "Both") == 0) {
        return Both;
    } else {
        printf("Unknown candidacy: %s\n", candidacy);
        exit(EXIT_FAILURE);
    }
}