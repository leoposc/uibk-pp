#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 500000000

int main(void) {
    int sum = 0;
    
    // measure time
    double start = omp_get_wtime();

#pragma omp parallel for proc_bind(master) num_threads(6)
    for (int i = 0; i < N; i++) {
        #pragma omp atomic
        sum += i;
    }

    double end = omp_get_wtime();
    printf("$!.//master: %f\n", end - start);

//     start = omp_get_wtime();
// {
//     // #pragma omp parallel for 
//     for (int i = 0; i < N; i++) {
//         #pragma omp atomic
//         sum += i;
//     }
// }
//     double end = omp_get_wtime();
//     printf("$!.//spread: %f\n", end - start);


//     start = omp_get_wtime();


// {
//     #pragma omp parallel for 
//     for (int i = 0; i < N; i++) {
//         #pragma omp atomic
//         sum += i;
//     }
// }
//     end = omp_get_wtime();
//     printf("$!.//close: %f\n", end - start);

//     start = omp_get_wtime();
// {
//     #pragma omp parallel for 
//     for (int i = 0; i < N; i++) {
//         #pragma omp atomic
//         sum += i;
//     }
// }
//     end = omp_get_wtime();
//     printf("$!.//close: %f\n", end - start);

//     start = omp_get_wtime();


// {
//     #pragma omp parallel for 
//     for (int i = 0; i < N; i++) {
//         #pragma omp atomic
//         sum += i;
//     }
// }
//     end = omp_get_wtime();
//     printf("$!.//master: %f\n", end - start);

    printf("Sum: %d\n", sum);
    return 0;
}
