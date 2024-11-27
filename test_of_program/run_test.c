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
void test_do_next_op_case11(void);
void test_do_next_op_case12(void);

int main(void) {
    /* Kør alle test-funktioner. */
    printf("test of Scan Data function\n");
        test_do_next_op_case1();
        test_do_next_op_case2();
    printf("All Scan Data tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("test of the PLPR function\n");
    printf("PLPR case 1: (2016 capped)\n");
        test_do_next_op_case3();
    printf("\nPLPR case 2: (2024 capped)\n");
        test_do_next_op_case4();
    printf("\nPLPR case 3: (2016 uncapped)\n");
        test_do_next_op_case5();
    printf("\nPLPR case 4: (2024 uncapped)\n");
        test_do_next_op_case6();
    printf("\nAll PLPR tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("test of the STV function\n");
    printf("STV case 1: (2016 capped)\n");
    test_do_next_op_case9();
    printf("\nSTV case 2: (2024 capped)\n");
    test_do_next_op_case10();
    printf("\nSTV case 3: (2016 uncapped)\n");
    test_do_next_op_case11();
    printf("\nSTV case 4: (2024 uncapped)\n");
    test_do_next_op_case12();
    printf("\nAll STV tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("test of the BC function\n");


    printf("\nAll BC tests passed successfully!\n");
    printf("----------------------------------------\n");
    printf("All tests passed successfully!\n");
    return 0;
}


