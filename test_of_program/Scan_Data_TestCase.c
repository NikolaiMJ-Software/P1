#include "../connecter.h"
#include <assert.h>

void test_do_next_op_case1(void);
void test_do_next_op_case2(void);
#define STATES 50



int main(void) {
    /* Kør alle test-funktioner. */
    test_do_next_op_case1();
    test_do_next_op_case2();

    printf("All tests passed successfully!\n");
    return 0;
}



void test_do_next_op_case1(void) {
    /* Arrange */
    states USA[STATES];

    // Call ScanData_TXT function to populate the USA array.
    ScanData_TXT(2016, USA);

    // Assertions to check that the first state's data is correct
    assert(strcmp(USA[0].stateName, "Alabama") == 0); // det virker :D
    assert(USA[0].electors == 9);
    assert(USA[0].democrats == 34.4);
    assert(USA[0].republicans == 62.1);
    assert(USA[0].population == 4863525);


    /* If everything is correct, the assertions will pass and the test will succeed. */
    printf("Test case 1 passed!\n");

}


void test_do_next_op_case2(void) {
    /* Arrange */
    states USA[STATES];

    // Call ScanData_TXT function to populate the USA array.
    ScanData_TXT(2016, USA);

    // Assertions to check that the first state's data is correct
    assert(strcmp(USA[31].stateName, "New York") == 0); // det virker igen :D
    assert(USA[31].electors == 29);
    assert(USA[31].democrats == 59.0);
    assert(USA[31].republicans == 36.5);
    assert(USA[31].population == 19633428);



    /* If everything is correct, the assertions will pass and the test will succeed. */
    printf("Test case 2 passed!\n");
}