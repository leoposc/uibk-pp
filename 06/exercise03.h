#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define B 3

void exercise03(int a[6][4]) {
#pragma omp parallel for simd collapse(2) shared(a)
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
// #pragma omp depend(in: a[i+2][j-1]) depend(out: a[i][j])          
            a[i + 2][j - 1] = B * a[i][j] + 4;
        }
    }

}