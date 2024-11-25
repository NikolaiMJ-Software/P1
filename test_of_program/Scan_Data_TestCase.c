#include "../connecter.h"
#include <assert.h>
void test_do_next_op_case1(void);
void test_do_next_op_case2(void);
void test_do_next_op_case3(void);
void test_do_next_op_case4(void);


int main(void) {
    /* Kør alle test-funktioner. */
    printf("test of Scan Data function\n");
        test_do_next_op_case1();
        test_do_next_op_case2();
    printf("All Scan Data tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("test of the PLPR function\n");
    printf("PLPR case 1:\n");

        test_do_next_op_case3();
    printf("\n");
    printf("PLPR case 1:\n");
        test_do_next_op_case4();
    printf("\n");
    printf("All PLPR tests passed successfully!\n");
    printf("----------------------------------------\n");

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
    assert(strcmp(USA[32].stateName, "New York") == 0); // det virker igen :D
    assert(USA[32].electors == 29);
    assert(USA[32].democrats == 59.0);
    assert(USA[32].republicans == 36.5);
    assert(USA[32].population == 19633428);



    /* If everything is correct, the assertions will pass and the test will succeed. */
    printf("Test case 2 passed!\n");
}

