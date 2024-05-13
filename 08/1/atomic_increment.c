#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_ITERATIONS 500000000

int main() {
	int counter = 0;
	double start_time, end_time;

	start_time = omp_get_wtime();

#pragma omp parallel for
	for (int i = 0; i < NUM_ITERATIONS; i++) {
#pragma omp atomic
		counter++;
	}

	end_time = omp_get_wtime();

	printf("Counter value after incrementing: %d\n", counter);
	printf("Time taken: %f seconds\n", end_time - start_time);

	return 0;
}
