#include "../connecter.h"
#include "../election_systems/PLPR.c"
#include "../Features/monte_carlo.c"
#include <assert.h>

void test_do_next_op_case3(void) {
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;
    // Populate the USA array
    ScanData_TXT(2016, USA);
    // Call PLPR with the populated dataset
    char* result = PLPR(USA, cap_systems, uncap_systems, counter_cap, counter_uncap, uncapped, states_abolished);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(cap_systems[counter_CMP].REP_electors == 250 && cap_systems[counter_CMP].DEM_electors == 257);

    printf("PLPR Test case 1 passed!\n");
}

void test_do_next_op_case4(void) {
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;

    // Populate the USA array
    ScanData_TXT(2024, USA);

    // Call PLPR with the populated dataset
    char* result = PLPR(USA, cap_systems,  uncap_systems, counter_cap, counter_uncap, uncapped, states_abolished);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(cap_systems[counter_CMP].REP_electors == 273 && cap_systems[counter_CMP].DEM_electors == 262);

    printf("PLPR Test case 2 passed!\n");
}//

void test_do_next_op_case5(void) {
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;
    cap_systems[0].year = 2016;
    // Populate the USA array
    ScanData_TXT(2016, USA);
    wyoming_rule(USA,cap_systems);

    // Call PLPR with the populated dataset
    char* result = PLPR(USA, cap_systems,  uncap_systems, counter_cap, counter_uncap, uncapped, states_abolished);
    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(cap_systems[counter_CMP].REP_electors == 292 && cap_systems[counter_CMP].DEM_electors == 305);

    printf("PLPR Test case 3 passed!\n");
}

void test_do_next_op_case6(void) {
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;
    cap_systems[0].year = 2024;
    // Populate the USA array
    ScanData_TXT(2024, USA);
    wyoming_rule(USA, cap_systems);

    // Call PLPR with the populated dataset
    char* result = PLPR(USA, cap_systems,  uncap_systems, counter_cap, counter_uncap, uncapped, states_abolished);
    // Check if result is not NULL

    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);
    assert(cap_systems[counter_CMP].REP_electors == 331 && cap_systems[counter_CMP].DEM_electors == 320);


    printf("PLPR Test case 4 passed!\n");
}