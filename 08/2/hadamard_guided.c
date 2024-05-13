#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void parallel_hadamard_product(double** a, double** b, double** c, size_t n) {
#pragma omp parallel for schedule(guided, 4) collapse(2)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}
}

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Usage: %s <n>\n", argv[0]);
		return 1;
	}
	size_t n = atoi(argv[1]);
	double** a = (double**)malloc(n * sizeof(double*));
	double** b = (double**)malloc(n * sizeof(double*));
	double** c = (double**)malloc(n * sizeof(double*));

	omp_set_num_threads(64);
#pragma omp for schedule(dynamic, 64)
	for(size_t i = 0; i < n; ++i) {
		a[i] = (double*)malloc(n * sizeof(double));
		b[i] = (double*)malloc(n * sizeof(double));
		c[i] = (double*)malloc(n * sizeof(double));
		for(size_t j = 0; j < n; ++j) {
			a[i][j] = 1.0;
			b[i][j] = 2.0;
		}
	}

	int num_threads[] = { 1, 2, 4, 6, 12 };
	for(int i = 0; i < 5; ++i) {
		omp_set_num_threads(num_threads[i]);
		double start_time = omp_get_wtime();
		parallel_hadamard_product(a, b, c, n);
		double end_time = omp_get_wtime();
		printf("%zu n, %d threads, parallel, time: %f seconds \n", n, num_threads[i],
		       end_time - start_time);
	}

	for(size_t i = 0; i < n; ++i) {
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	free(a);
	free(b);
	free(c);

	return 0;
}
