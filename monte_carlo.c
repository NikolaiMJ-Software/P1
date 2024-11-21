#include "connecter.h"
#include <time.h>
#define comparisons 50000
// Monte Carlo study
void monte_carlo() {
    // input of how many chose the third-party

    // restart rand
    srand(time(NULL));

    for(int i = 0; i < comparisons; i++) {
        int r_number = rand() % 2;

    }
}