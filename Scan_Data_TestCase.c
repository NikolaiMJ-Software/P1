
#include "Scan_data_TXT.h"
void test_do_next_op_case1(void);
void test_do_next_op_case2(void);



int main(void) {
    /* Kør alle test-funktioner. */
    test_do_next_op_case1();
    test_do_next_op_case2();
    test_do_next_op_example_sequence();
}

void test_do_next_op_case1(void) {
    /* Arrange /
    int n = 128;
    double expected = 6.278594;

    / Act /
    double a = -2;
    double b = 2;



    double result = trap(a, b, n, h);

    / Assert */
    assert(is_almost_equal(result, expected));
}
