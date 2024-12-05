#include "../connecter.h"
//
// Created by Nikolai on 27-11-2024.
//

/*information pages regarding candidate members:
https://en.wikipedia.org/wiki/List_of_United_States_presidential_candidates
https://en.wikipedia.org/wiki/2024_United_States_presidential_election
https://en.wikipedia.org/wiki/2020_United_States_presidential_election
https://en.wikipedia.org/wiki/2016_United_States_presidential_election
https://en.wikipedia.org/wiki/2008_United_States_presidential_election
https://en.wikipedia.org/wiki/2012_United_States_presidential_election
*/
Party string_to_party(const char* party);
Candidacy string_to_candidacy(const char* candidacy);

int ScanCandidatesTXT(int input_year, candidates* candidate_list) {
    //define file size
    char filename[50];
    //choose specific file depending on input year
    snprintf(filename, sizeof(filename), "Candidates/Candidates_%d.txt", input_year);

    //Open file, and see if file exists
    FILE* inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    //buffer
    char line[100];
    int i = 0;

    //scanning data while loop
    while (fgets(line, sizeof(line), inputFile) && i<CANDIDATES) {
        char party_string[20], name_string[NAME_LGT], candidacy_string[20];
        int p_popularity = 0, vp_popularity = 0;

        //scan data in form of chars, and return an error if not possible
        if (sscanf(line, "%19[^,], %49[^,], %19[^,], %d, %d", party_string, name_string, candidacy_string, &p_popularity, &vp_popularity) != 5) {
            printf("Error reading line: %s\n", line);
            fclose(inputFile);
            return 0;
        }

        //cutting out space
        strtok(party_string, " ");
        strtok(candidacy_string, " ");

        //converting party to 0, 1 or 2
        candidate_list[i].party = string_to_party(party_string);
        //making name string valid, by inserting \0
        strncpy(candidate_list[i].name, name_string, NAME_LGT-1);
        candidate_list[i].name[NAME_LGT-1] = '\0';
        //converting candidacy to 0, 1 or 2
        candidate_list[i].candidacy = string_to_candidacy(candidacy_string);
        // Storing popularity percentages
        candidate_list[i].p_popularity_percentage = p_popularity;
        candidate_list[i].vp_popularity_percentage = vp_popularity;
        candidate_list[i].p_votes = 0;
        candidate_list[i].vp_votes = 0;
        //test function, to see if properly inserted
        //printf("Party: %d Name: %s Candidacy: %d p_popularity: %d vp_popularity: %d votes: %d\n", candidate_list[i].party, candidate_list[i].name, candidate_list[i].candidacy, candidate_list[i].p_popularity_percentage, candidate_list[i].vp_popularity_percentage, candidate_list[i].votes);

        i++;
    }

    fclose(inputFile);
    return 1;
}

//convert party to int function
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

//convert candidacy to in function
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