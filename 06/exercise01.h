#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 5

void exercise01_01(int n, int *x, int *y) {
    // #pragma omp parallel for collapse(2) simd reduction(+:x)
    for (int i=0; i < n-1; i++) {
        for (int j=0; j < n-1; j++) {
            x[i] = (y[i] + x[i+1]) / 7;
        }
    }
}


void exercise01_02(int n, int *x, int *y, int *z, int *a, int *f) {
    for (int i=0; i < n; i++) {
        *a = (x[i] + y[i]) / (i+1);
        z[i] = &a;
    }

    *f = sqrt(a + A);
}


void exercise01_03(int n, int *x, int *y, int *z) {
    for (int i=0; i < n; i++) {
        x[i] = y[i] * 2 + b * i;
    }


    for (int i=0; i < n; i++) {
        y[i] = x[i]  + A / (i+1);
    }
}