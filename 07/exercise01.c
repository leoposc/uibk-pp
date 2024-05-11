// testing for exercise 1, 2 

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../unity/unity.h"

#define N 1000000

void setUp(void) {
    // set stuff up here    
}

void tearDown(void) {
    // clean stuff up here    
}

void test_exercise01(void) {
    //test stuff
    int32_t* aO = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* bO = (int32_t*) malloc(N * sizeof(int32_t));

    //measure time
    double start_time_optimized = omp_get_wtime();

    aO[0] = 0;
    bO[0] = 0;
    #pragma omp parallel for simd
    for (int i=1; i<N; i++) {
        aO[i] = 2.0*i*(i-1);        
    }

    // add a and a_cpy and store in b
    #pragma omp parallel for simd
    for (int i=1; i<N; i++) {
        bO[i] = aO[i] - aO[i-1];
    }

    double end_time_optimized = omp_get_wtime();

    int32_t* a = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* b = (int32_t*) malloc(N * sizeof(int32_t));

    //measure time
    double start_time = omp_get_wtime();

    a[0] = 0;
    b[0] = 0;
    for (int i=1; i<N; i++) {
        a[i] = 2.0*i*(i-1);
        b[i] = a[i] - a[i-1];
    }

    double end_time = omp_get_wtime();

    TEST_ASSERT_EQUAL_INT32_ARRAY(a, aO, N);
    TEST_ASSERT_EQUAL_INT32_ARRAY(b, bO, N);

    double optimized = end_time_optimized - start_time_optimized;
    double not_optimized = end_time - start_time;

    printf("First Code snippet. Optimized: %f vs. not optimized: %f\n", optimized, not_optimized);
    printf("Speedup: %f\n", not_optimized/optimized);

    free(a);
    free(b);
}

// ------------------------------------------------------------------------

void test_exercise02(void) {
    //test stuff
    int32_t* aO = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* bO = (int32_t*) malloc(N * sizeof(int32_t));

    //measure time
    double start_time_optimized = omp_get_wtime();

    aO[0] = 0;
    bO[0] = 0;
    int i;

    #pragma omp parallel
    {
        #pragma omp for simd schedule (static) 
        for (i=1; i<N; i++) {
            aO[i] = 3.0*i*(i+1);
        }
        #pragma omp for schedule (static)
        for (i=1; i<N; i++) {
            bO[i] = aO[i] - aO[i-1];
        }
    }

    double end_time_optimized = omp_get_wtime();

    int32_t* a = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* b = (int32_t*) malloc(N * sizeof(int32_t));

    //measure time
    double start_time = omp_get_wtime();

    a[0] = 0;
    b[0] = 0;
            
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1);
    }
    
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
    

    double end_time = omp_get_wtime();


    TEST_ASSERT_EQUAL_INT32_ARRAY(a, aO, N);
    TEST_ASSERT_EQUAL_INT32_ARRAY(b, bO, N);

    double optimized = end_time_optimized - start_time_optimized;
    double not_optimized = end_time - start_time;

    printf("Second Code snippet. Optimized: %f vs. not optimized: %f\n", optimized, not_optimized);
    printf("Speedup: %f\n", not_optimized/optimized);

    free(a);
    free(b);
}


// ------------------------------------------------------------------------

void test_exercise03(void) {
    //test stuff
    int32_t* aO = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* bO = (int32_t*) malloc(N * sizeof(int32_t));

    //measure time
    double start_time_optimized = omp_get_wtime();

    aO[0] = 0;
    int i, x;

    for (i=0; i<N; i++) {
        bO[i] = 3 * i;
    }

    #pragma omp parallel for private(x)
    for (i=1; i<N; i++) {
        x = sqrt(bO[i]) - 1;
        aO[i] = x*x + 2*x + 1;
    }

    double end_time_optimized = omp_get_wtime();

    int32_t* a = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* b = (int32_t*) malloc(N * sizeof(int32_t));

    //measure time
    double start_time = omp_get_wtime();

    a[0] = 0;
    
            
    for (i=0; i<N; i++) {
        b[i] = 3 * i;
    }

    for (i=1; i<N; i++) {
        x = sqrt(b[i]) - 1;
        a[i] = x*x + 2*x + 1;
    }
    

    double end_time = omp_get_wtime();


    TEST_ASSERT_EQUAL_INT32_ARRAY(a, aO, N);

    double optimized = end_time_optimized - start_time_optimized;
    double not_optimized = end_time - start_time;

    printf("Second Code snippet. Optimized: %f vs. not optimized: %f\n", optimized, not_optimized);
    printf("Speedup: %f\n", not_optimized/optimized);

    free(a);
    free(b);
}

// ------------------------------------------------------------------------

void test_exercise04(void) {
    //test stuff
    int32_t* aO = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* bO = (int32_t*) malloc(N * sizeof(int32_t));

    aO[0] = 0;
    int const f = 2;
    int i, x;

    for (i=0; i<N; i++) {
        bO[i] = 3 * i;
    }

    //measure time
    double start_time_optimized = omp_get_wtime();


    #pragma omp parallel for lastprivate(x)
    for (i=1; i<N; i++) {
        x = f * bO[i];
        aO[i] = x - 7;
    }
    aO[0] = x;

    double end_time_optimized = omp_get_wtime();

    int32_t* a = (int32_t*) malloc(N * sizeof(int32_t));
    int32_t* b = (int32_t*) malloc(N * sizeof(int32_t));


    a[0] = 0;

    for (i=0; i<N; i++) {
        b[i] = 3 * i;
    }

    //measure time
    double start_time = omp_get_wtime();

    for (i=1; i<N; i++) {
        x = f * b[i];
        a[i] = x - 7;
    }
    a[0] = x; 
    

    double end_time = omp_get_wtime();


    TEST_ASSERT_EQUAL_INT32_ARRAY(a, aO, N);

    double optimized = end_time_optimized - start_time_optimized;
    double not_optimized = end_time - start_time;

    printf("Second Code snippet. Optimized: %f vs. not optimized: %f\n", optimized, not_optimized);
    printf("Speedup: %f\n", not_optimized/optimized);

    free(a);
    free(b);
}

// ------------------------------------------------------------------------

void test_exercise05(void) {
    //test stuff
    int32_t* bO = (int32_t*) malloc(N * sizeof(int32_t));

    //measure time
    double start_time_optimized = omp_get_wtime();


    int i;

    for (i=0; i<N; i++) {
        bO[i] = 3 * i;
    }

    int sumO = 0; 
    #pragma omp parallel for reduction(+:sumO)
    for (i=1; i<N; i++) {
        sumO = sumO + bO[i];
    }
    

    double end_time_optimized = omp_get_wtime();

    int32_t* b = (int32_t*) malloc(N * sizeof(int32_t));
            
    for (i=0; i<N; i++) {
        b[i] = 3 * i;
    }

    //measure time
    double start_time = omp_get_wtime();

    int sum = 0; 
    for (i=1; i<N; i++) {
        sum = sum + b[i];
    }
    

    double end_time = omp_get_wtime();


    TEST_ASSERT_EQUAL_INT(sum, sumO);

    double optimized = end_time_optimized - start_time_optimized;
    double not_optimized = end_time - start_time;

    printf("Second Code snippet. Optimized: %f vs. not optimized: %f\n", optimized, not_optimized);
    printf("Speedup: %f\n", not_optimized/optimized);

    free(b);
}

// ------------------------------------------------------------------------

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_exercise01);
    RUN_TEST(test_exercise02);
    RUN_TEST(test_exercise03);
    RUN_TEST(test_exercise04);
    RUN_TEST(test_exercise05);
    return UNITY_END();
}
