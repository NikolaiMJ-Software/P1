#include "../connecter.h"
#include <assert.h>
void test_do_next_op_case7(void) {
    int activate_progress = false;
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;

    // Populate the USA array
    ScanData_TXT(2016, USA);

    // Call STV with the populated dataset
    char* result = STV(USA, cap_systems, uncap_systems, activate_progress, counter_cap, counter_uncap, states_abolished, uncapped);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 1 passed!\n");
}

void test_do_next_op_case8(void) {
    int activate_progress = false;
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;

    // Populate the USA array
    ScanData_TXT(2024, USA);

    // Call STV with the populated dataset
    char* result = STV(USA, cap_systems, uncap_systems, activate_progress, counter_cap, counter_uncap, states_abolished, uncapped);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 2 passed!\n");
}

void test_do_next_op_case9(void) {
    int activate_progress = false;
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;
    cap_systems[0].year = 2016;
    // Populate the USA array
    ScanData_TXT(2016, USA);
    wyoming_rule(USA,cap_systems);

    // Call STV with the populated dataset
    char* result = STV(USA, cap_systems, uncap_systems, activate_progress, counter_cap, counter_uncap, states_abolished, uncapped);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 3 passed!\n");
}

void test_do_next_op_case10(void) {
    int activate_progress = false;
    int counter_CMP = 0;
    states USA[STATES];
    cmp cap_systems[3];
    cmp uncap_systems[3];
    int states_abolished = 0, uncapped = 0,counter_cap = 0, counter_uncap = 0;
    cap_systems[0].year = 2024;
    // Populate the USA array
    ScanData_TXT(2024, USA);
    wyoming_rule(USA,cap_systems);

    // Call STV with the populated dataset
    char* result = STV(USA, cap_systems, uncap_systems, activate_progress, counter_cap, counter_uncap, states_abolished, uncapped);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 4 passed!\n");
}