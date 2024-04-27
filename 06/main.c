// testing for exercise 1, 2 and 3

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "exercise01.h"
#include "../unity/unity.h"

#define A 5

void setUp(void) {
    // set stuff up here    
}

void tearDown(void) {
    // clean stuff up here    
}

void test_exercise01_01(void) {
    //test stuff
    const int n = 10;
    int32_t *actual_x = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *actual_y = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *x = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *y = (int32_t *) malloc(n * sizeof(int32_t));

    for (int i=0; i < n; i++) {
        actual_x[i] = 1;
        actual_y[i] = 2;
        x[i] = 1;
        y[i] = 2;
    }

    for (int i=0; i < n-1; i++) {
        x[i] = (y[i] + x[i+1]) / 7;
    }
    exercise01_01(n, actual_x, actual_y);
    TEST_ASSERT_EQUAL_INT32_ARRAY(x, actual_x, n);

    free(actual_x);
    free(actual_y);
    free(x);
    free(y);
}

void test_exercise01_02(void) {
    //test stuff
    const int n = 10;
    int32_t *actual_x = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *actual_y = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *actual_z = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *x = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *y = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *z = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t a, f;
    int32_t actual_f;

    for (int i=0; i < n; i++) {
        actual_x[i] = 1;
        actual_y[i] = 2;
        x[i] = 1;
        y[i] = 2;
    }

    for (int i=0; i < n; i++) {
        a = (x[i] + y[i]) / (i+1);
        z[i] = a;
    }

    f = sqrt(a + A);

    exercise01_03(n, actual_x, actual_y, actual_z, &actual_f);

    TEST_ASSERT_EQUAL_INT32_ARRAY(z, actual_z, n);
    TEST_ASSER_EQUAL_INT32(f, actual_f);

    free(actual_x);
    free(actual_y);
    free(x);
    free(y);
}

void test_exercise01_03(void) {
    //test stuff
    const int n = 10;
    int32_t *actual_x = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *actual_y = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *x = (int32_t *) malloc(n * sizeof(int32_t));
    int32_t *y = (int32_t *) malloc(n * sizeof(int32_t));

    for (int i=0; i < n; i++) {
        actual_x[i] = 1;
        actual_y[i] = 2;
        x[i] = 1;
        y[i] = 2;
    }

    for (int i=0; i < n; i++) {
        x[i] = y[i] * 2 + A * i;
    }


    for (int i=0; i < n; i++) {
        y[i] = x[i]  + A / (i+1);
    }

    exercise01_03(n, actual_x, actual_y);
    TEST_ASSERT_EQUAL_INT32_ARRAY(x, actual_x, n);
    TEST_ASSERT_EQUAL_INT32_ARRAY(y, actual_y, n);

    free(actual_x);
    free(actual_y);
    free(x);
    free(y);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_exercise01_01);
    // RUN_TEST(test_exercise01_02);
    // RUN_TEST(test_exercise01_03);
    return UNITY_END();
}
