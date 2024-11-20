
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../connecter.h"

void test_do_next_op_case1(void);
//void test_do_next_op_case2(void);
#define STATES 50



int main(void) {
    /* Kør alle test-funktioner. */
    test_do_next_op_case1();
  //  test_do_next_op_case2();
}

void test_do_next_op_case1(void) {
    /* Arrange */
    states USA[STATES];

    // Call ScanData_TXT function to populate the USA array.
    ScanData_TXT(2016);

    // Assertions to check that the first state's data is correct
    assert(strcmp(USA[0].stateName, "Alabama") == 0);
    assert(USA[0].electors == 9);
    assert(USA[0].democrats == 34.4);
    assert(USA[0].republicans == 62.1);
    assert(USA[0].population == 4863525);

    /* If everything is correct, the assertions will pass and the test will succeed. */
}


