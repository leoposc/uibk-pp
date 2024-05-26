#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

#define REPETITIONS 1000000

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);

    float *a = (float *) _mm_malloc(size * sizeof(float), 16);
    float *b = (float *) _mm_malloc(size * sizeof(float), 16);
    float *c = (float *) _mm_malloc(size * sizeof(float), 16);

    for(int i = 0; i < size; ++i) {
        a[i] = 0;
        b[i] = i;
        c[i] = (i/2.0) - i;
    }

     // measure time
    double start = omp_get_wtime();

    // thanks chatGPT (for-loop)
    for(int run = 0; run < REPETITIONS; ++run) {
        for(int i = 0; i < size; i += 4) {
            // Load 4 floats from b and c
            __m128 b_vals = _mm_load_ps(&b[i]);
            __m128 c_vals = _mm_load_ps(&c[i]);

            // Multiply b and c
            __m128 bc_mult = _mm_mul_ps(b_vals, c_vals);

            // Load 4 floats from a
            __m128 a_vals = _mm_load_ps(&a[i]);

            // Add the result to a
            a_vals = _mm_add_ps(a_vals, bc_mult);

            // Store the result back in a
            _mm_store_ps(&a[i], a_vals);
        }
    }

    double end = omp_get_wtime();

    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
    }
    printf("sum = %f\n", sum);
    printf("$!%s: %f\n",argv[0], end - start);

    _mm_free(a);
    _mm_free(b);
    _mm_free(c);

    return 0;
}
