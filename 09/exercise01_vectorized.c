#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define REPETITIONS 1000000

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);

    int a[size], b[size], c[size];

    for(int i = 0; i < size; ++i) {
        a[i] = 0;
        b[i] = i;
        c[i] = (i/2) - i;
    }

     // measure time
    double start = omp_get_wtime();

    for(int run = 0; run < REPETITIONS; ++run) {
        for(int i = 0; i < size; ++i) {
            a[i] += b[i] * c[i];
        }
    }

    double end = omp_get_wtime();

    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
    }
    printf("sum = %d\n", sum);
    printf("$!%s: %f\n",argv[0], end - start);

    return 0;
}
