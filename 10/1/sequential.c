#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int D(int m, int n) {
	if (m == 0 || n == 0) {
		return 1;
	} else {
		return D(m-1, n) + D(m-1, n-1) + D(m, n-1);
	}
}

void print_dallanoy_number(int n, int **D) {
	printf("D[n-1] [n-1]: %d \n", D[n - 1][n - 1]);
}

void compute_print_measureTime_matrix(int n, int **D) {
	double start_time = omp_get_wtime();
	for (int m = 0; m < n; m++) {
		for (int p = 0; p < n; p++) {
			if (m == 0 || p == 0) {
				D[m][p] = 1;
			} else {
				D[m][p] = D[m-1][p] + D[m-1][p-1] + D[m][p-1];
			}
		}
	}
	double end_time = omp_get_wtime();
	printf("Elapsed time: %f seconds\n", end_time - start_time);
	print_dallanoy_number(n, D);
}

int main(int argc, char** argv) {
	if(argc != 2) return 1;
	int n = atoi(argv[1]);
	int result = 0;

	double start_time = omp_get_wtime();
	result = D(n, n);
	double end_time = omp_get_wtime();
	printf("Elapsed time: %f seconds\n", end_time - start_time);
	printf("Result: %d", result);

	/*
	int **D = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++) {
		D[i] = (int *)malloc(n * sizeof(int));
	}

	compute_print_measureTime_matrix(n, D);

	// Free the dynamically allocated memory
	for (int i = 0; i < n; i++) {
		free(D[i]);
	}
	free(D);
	 */

	return 0;
}
