#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 5
#define B 3

void exercise01_01(int n, int *x, int *y) {
#pragma omp parallel for simd aligned(x, y: 64) shared(x, y) 
    for (int i=0; i < n-1; i++) {
        x[i] = (y[i] + x[i+1]) / 7;
    }
}


void exercise01_02(int n, int *x, int *y, int *z, int *f) {
int a;
#pragma omp parallel for simd shared(x, y, z, f) lastprivate(a) 
    for (int i=0; i < n; i++) {
        a = (x[i] + y[i]) / (i+1);
        z[i] = a;
    }

    *f = sqrt(a + A);
}


void exercise01_03(int n, int *x, int *y) {
#pragma omp parallel for simd shared(x, y) 
    for (int i=0; i < n; i++) {
        x[i] = y[i] * 2 + B * i;
    }


#pragma omp parallel for simd shared(x, y) 
    for (int i=0; i < n; i++) {
        y[i] = x[i]  + A / (i+1);
    }
}