#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../unity/unity.h"

#define N 1000

void setUp(void) {
    // set stuff up here    
}

void tearDown(void) {
    // clean stuff up here    
}

void copy(double* x, double* y) {
    #pragma omp parallel for simd
    for(int i = 0; i < N; i++) {
        x[i] = y[i];
    }
}

void test_exercise01(void) {

    double* xP = (double*) malloc(N * sizeof(double));
    double* yP = (double*) malloc(N * sizeof(double));

    for (int i=0; i<N; i++) {
        xP[i] = 2.0*i*(i-1);        
    }

    copy(yP, xP);

    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(xP, yP, N);    
}


void test_exercise02(void) {
    
    int32_t* A = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* B = (int32_t*) malloc(N * sizeof(int32_t));

    for (int i = 0; i <N; i++) {
        A[i] = 1;
        B[i] = 1;
    }

    for (int i=4; i<=N; i+=9) {
        for (int j=0; j<=N; j+=5) {
            A[i] = 0;
        }
    }

    // normalize the loop
    for (int i = 0; i < N / 9; i++) {
        B[4 + 9 * i] = 0;
    }

    TEST_ASSERT_EQUAL_INT32_ARRAY(A, B, N);    
}


void test_exercise03(void) {
    
    // int32_t* A = (int32_t*) malloc(N * sizeof(int32_t));
    // int32_t* B = (int32_t*) malloc(N * sizeof(int32_t));

    int32_t A[10][10][10];
    int32_t B[10][10][10];

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(int k = 0; k < 10; k++) {
                A[i][j][k] = 0;
                B[i][j][k] = 0;
            }
        }
    }

    /* can not parallize the following loop since it has a true
     * dependency on the previous iteration. The value of A[i+1][j][k-1]
     * depends on the value of A[i][j][k] which is calculated in the
     * previous iteration. The distance vector is 1, 0, -1 and the direction
     * vector is (<, =, >) so the loop can not be parallelized.
     */

    for(int i = 1; i < 9; i++) {
        for(int j = 1; j < 9; j++) {
            for(int k = 1; k < 9; k++) {
                A[i+1][j][k-1] = A[i][j][k] + 5;
            }
        }
    }

    for(int i = 1; i < 9; i++) {
        for(int j = 1; j < 9; j++) {
            for(int k = 1; k < 9; k++) {
                B[i+1][j][k-1] = B[i][j][k] + 5;
            }
        }
    }

    int32_t* test_a;
    int32_t* test_b;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            test_a = &A[i][j][0];
            test_b = &B[i][j][0];
            TEST_ASSERT_EQUAL_INT32_ARRAY(test_a, test_b, 10);
        }
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_exercise01);
    RUN_TEST(test_exercise02);
    RUN_TEST(test_exercise03);
    return UNITY_END();
}
