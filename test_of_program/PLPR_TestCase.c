#include "../connecter.h"
#include "../election_systems/PLPR.c"
#include "../monte_carlo.c"
#include <assert.h>

void test_do_next_op_case3(void);
void test_do_next_op_case4(void);
void test_do_next_op_case5(void);


void test_do_next_op_case3(void) {
    states USA[STATES];

    // Populate the USA array
    ScanData_TXT(2016, USA);

    // Call PLPR with the populated dataset
    char* result = PLPR(USA);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("PLPR Test case 1 passed!\n");
}

void test_do_next_op_case4(void) {
    states USA[STATES];

    // Populate the USA array
    ScanData_TXT(2024, USA);

    // Call PLPR with the populated dataset
    char* result = PLPR(USA);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("PLPR Test case 2 passed!\n");
}//

void test_do_next_op_case5(void) {
    states USA[STATES];
    //char wyoming_rule_true = 'n';

    // Populate the USA array
    wyoming_rule(2016, USA);

    // Call PLPR with the populated dataset
    char* result = PLPR(USA);

    // Check if result is not NULL
    assert(result != NULL);
    //assert(&wyoming_rule_true == 'y');

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("PLPR Test case 3 passed!\n");
}