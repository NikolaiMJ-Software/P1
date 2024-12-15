#include "../connecter.h"
// Scan_data
void test_do_next_op_case1(void);
void test_do_next_op_case2(void);

// PLPR
void test_do_next_op_case3(void);
void test_do_next_op_case4(void);
void test_do_next_op_case5(void);
void test_do_next_op_case6(void);

// STV
void test_do_next_op_case7(void);
void test_do_next_op_case8(void);
void test_do_next_op_case9(void);
void test_do_next_op_case10(void);

// BC
void test_do_next_op_case11(void);
void test_do_next_op_case12(void);
void test_do_next_op_case13(void);
void test_do_next_op_case14(void);


int main(void) {
    // Run all test functions
    printf("Initiating test functions\n");
    printf("----------------------------------------\n");
    printf("test of Scan Data function\n");
        test_do_next_op_case1();
        test_do_next_op_case2();
    printf("All Scan Data tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("test of the PLPR function\n");
    printf("---PLPR case 1: (2016 capped)---\n");
        test_do_next_op_case3();
    printf("\n---PLPR case 2: (2024 capped)---\n");
        test_do_next_op_case4();
    printf("\n---PLPR case 3: (2016 uncapped)---\n");
        test_do_next_op_case5();
    printf("\n---PLPR case 4: (2024 uncapped)---\n");
        test_do_next_op_case6();
    printf("\nAll PLPR tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("test of the STV function\n");
    printf("---STV case 1: (2016 capped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case7();
    printf("\n---STV case 2: (2024 capped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case8();
    printf("\n---STV case 3: (2016 uncapped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case9();
    printf("\n---STV case 4: (2024 uncapped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case10();
    printf("\nAll STV tests passed successfully!\n");
    printf("----------------------------------------\n");

    printf("test of the BC function\n");
    printf("---BC case 1: (2016 capped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case11();
    printf("\n---BC case 2: (2024 capped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case12();
    printf("\n---BC case 3: (2016 uncapped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case13();
    printf("\n---BC case 4: (2024 uncapped)---\n");
    printf("\n----please wait----\n");
    test_do_next_op_case14();
    printf("\nAll BC tests passed successfully!\n");
    printf("----------------------------------------\n");
    printf("All tests passed successfully!\n");
    return 0;
}


