#include "../connecter.h"
#include <assert.h>

void test_do_next_op_case9(void) {
    states USA[STATES];

    // Populate the USA array
    ScanData_TXT(2016, USA);

    // Call STV with the populated dataset
    char* result = STV(USA);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 1 passed!\n");
}

void test_do_next_op_case10(void) {
    states USA[STATES];

    // Populate the USA array
    ScanData_TXT(2024, USA);

    // Call STV with the populated dataset
    char* result = STV(USA);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 2 passed!\n");
}

void test_do_next_op_case11(void) {
    states USA[STATES];

    // Populate the USA array
    ScanData_TXT(2016, USA);
    wyoming_rule(2016, USA);

    // Call STV with the populated dataset
    char* result = STV(USA);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Democrats"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 3 passed!\n");
}

void test_do_next_op_case12(void) {
    states USA[STATES];

    // Populate the USA array
    ScanData_TXT(2024, USA);
    wyoming_rule(2024, USA);

    // Call STV with the populated dataset
    char* result = STV(USA);

    // Check if result is not NULL
    assert(result != NULL);

    // Check the expected result
    char* expected_result = "Republicans"; // Modify this based on the expected winner for your data

    // Print the result and assert the outcome
    printf("Expected: '%s', Got: '%s'\n", expected_result, result);
    assert(strcmp(result, expected_result) == 0);

    printf("STV Test case 4 passed!\n");
}