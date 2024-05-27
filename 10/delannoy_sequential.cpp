#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <omp.h>

int delannoy(int n, int m)
{
    // Base case
    if (m == 0 || n == 0)
        return 1;
 
    // Recursive step.
    return delannoy(m - 1, n) + 
            delannoy(m - 1, n - 1) +
            delannoy(m, n - 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    printf("threads: %d\n", omp_get_max_threads());
    int size = atoi(argv[1]);

    double start = omp_get_wtime();
    int result = delannoy(size, size);
    double end = omp_get_wtime();

    printf("Delannoy(%d) = %d\n", size, result);
    printf("$!%s: %f seconds\n", argv[0], end - start);

    return 0;
}
