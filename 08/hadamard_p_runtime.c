#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    int **a = malloc(n * sizeof(int *));
    int **b = malloc(n * sizeof(int *));
    int **c = malloc(n * sizeof(int *));

    #pragma omp parallel for schedule(runtime) 
    for (int i = 0; i < n; ++i) {
        a[i] = malloc(n * sizeof(int));
        b[i] = malloc(n * sizeof(int));
        c[i] = malloc(n * sizeof(int));
    }

    #pragma omp parallel for schedule(runtime) 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }
    }

     // measure time
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(runtime) 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    double end = omp_get_wtime();
    printf("$!%s_%d_%d: %f\n",argv[0], n, omp_get_max_threads(), end - start);

    return 0;
}
