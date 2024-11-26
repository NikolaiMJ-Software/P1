#include "../connecter.h"
#include <assert.h>
//scan_data
void test_do_next_op_case1(void);
void test_do_next_op_case2(void);

//PLPR
void test_do_next_op_case3(void);
void test_do_next_op_case4(void);
void test_do_next_op_case5(void);
void test_do_next_op_case6(void);

//BC
void test_do_next_op_case7(void);
void test_do_next_op_case8(void);

//STV
void test_do_next_op_case9(void);
void test_do_next_op_case10(void);

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
    printf("PLPR case 2:\n");
        test_do_next_op_case4();
    printf("\n");
    printf("All PLPR tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("All tests passed successfully!\n");
    return 0;
}


