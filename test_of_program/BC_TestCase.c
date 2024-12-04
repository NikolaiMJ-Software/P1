#include "../connecter.h"
#include <assert.h>

void test_do_next_op_case11(void) {
    int activate_progress = false;
    int counter_CMP = 3;
    states USA[STATES];
    cmp e_systems[3];
    cmp* uncap_systems;
    int states_abolished, uncapped;

    // Populate the USA array
    ScanData_TXT(2016, USA);

    // Call STV with the populated dataset
    char* result = BC(USA, e_systems, uncap_systems, activate_progress, counter_CMP, uncapped);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(e_systems[counter_CMP].REP_electors == 199 && e_systems[counter_CMP].DEM_electors == 202);

    printf("BC Test case 1 passed!\n");
}


void test_do_next_op_case12(void) {
    int activate_progress = false;
    int counter_CMP = 3;
    states USA[STATES];
    cmp e_systems[3];
    cmp* uncap_systems;
    int states_abolished, uncapped;

    // Populate the USA array
    ScanData_TXT(2024, USA);

    // Call STV with the populated dataset
    char* result = BC(USA, e_systems, uncap_systems, activate_progress, counter_CMP, uncapped);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(e_systems[counter_CMP].REP_electors == 206 && e_systems[counter_CMP].DEM_electors == 202);

    printf("BC Test case 2 passed!\n");
}

void test_do_next_op_case13(void) {
    int activate_progress = false;
    int counter_CMP = 3;
    states USA[STATES];
    cmp e_systems[3];
    cmp* uncap_systems;
    int states_abolished, uncapped;

    // Populate the USA array
    ScanData_TXT(2016, USA);
    wyoming_rule(2016, USA);

    // Call STV with the populated dataset
    char* result = BC(USA, e_systems, uncap_systems, activate_progress, counter_CMP, uncapped);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(e_systems[counter_CMP].REP_electors == 233 && e_systems[counter_CMP].DEM_electors == 238);

    printf("BC Test case 3 passed!\n");
}

void test_do_next_op_case14(void) {
    int activate_progress = false;
    int counter_CMP = 3;
    states USA[STATES];
    cmp e_systems[3];
    cmp* uncap_systems;
    int states_abolished, uncapped;

    // Populate the USA array
    ScanData_TXT(2024, USA);
    wyoming_rule(2024, USA);

    // Call STV with the populated dataset
    char* result = BC(USA, e_systems, uncap_systems, activate_progress, counter_CMP, uncapped);
    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(e_systems[counter_CMP].REP_electors == 250 && e_systems[counter_CMP].DEM_electors == 246);


    printf("BC Test case 4 passed!\n");
}