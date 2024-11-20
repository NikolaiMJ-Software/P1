
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "connecter.h"
void test_do_next_op_case1(void);
void test_do_next_op_case2(void);
#define STATES 50



int main(void) {
    /* Kør alle test-funktioner. */
    test_do_next_op_case1();
    test_do_next_op_case2();
}

void ScanData_TXT(int input_year, states * usa);

void test_do_next_op_case1(void) {
    /* Arrange */
    states USA[STATES];

    // Call ScanData_TXT function to populate the USA array.
    ScanData_TXT(2016, USA); // Fixed: Missing semicolon here

    // Assertions to check that the first state's data is correct
    assert(strcmp(USA[0].stateName, "Nebraska") == 0);
    assert(USA[0].electors == 5);
    assert(USA[0].democrats == 33.7);
    assert(USA[0].republicans == 58.7);
    assert(USA[0].population == 1905616);

    /* If everything is correct, the assertions will pass and the test will succeed. */
}

}
