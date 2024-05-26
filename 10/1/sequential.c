#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_matrix(int n, int **D) {
	printf("D[n-1] [n-1]: %d \n", D[n-1] [n-1]);
	/*
	for (int m = 0; m < n; m++) {
		for (int p = 0; p < n; p++) {
			printf("%d ", D[m][p]);
		}
		printf("\n");
	}
	 */
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
	print_matrix(n, D);
}

int main(int argc, char** argv) {
	if(argc != 2) return 1;
	int n = atoi(argv[1]);

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

	return 0;
}
