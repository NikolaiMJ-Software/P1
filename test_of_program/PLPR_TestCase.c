#include "../connecter.h"
#include "../election_systems/PLPR.c"
#include <assert.h>

void test_do_next_op_case3(void);

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

    printf("PLPR Test case passed!\n");
}