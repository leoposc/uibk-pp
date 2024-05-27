#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <omp.h>

int delannoy(int m, int n, int depth_limit) {     
    // Base case
    if (m == 0 || n == 0) return 1;

    int result1, result2, result3;

    if (depth_limit > 0) {
        {
        #pragma omp task shared(result1) 
            result1 = delannoy(m - 1, n, depth_limit - 1);
        #pragma omp task shared(result2) 
            result2 = delannoy(m - 1, n - 1, depth_limit - 1);
        #pragma omp task shared(result3) 
            result3 = delannoy(m, n - 1, depth_limit - 1); 
        }
    } else {
        result1 = delannoy(m - 1, n, depth_limit);
        result2 = delannoy(m - 1, n - 1, depth_limit);
        result3 = delannoy(m, n - 1, depth_limit);
    }


#pragma omp taskwait
    
    return result1 + result2 + result3;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int result;

    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            result = delannoy(size, size, 4);
        }   
    }
    double end = omp_get_wtime();

    printf("Delannoy(%d) = %d\n", size, result);
    printf("$!%s: %f seconds\n", argv[0], end - start);

    return 0;
}
