#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define S 10

int D(int m, int n) {
	if(m == 0 || n == 0) {
		return 1;
	}
	if(m + n < 15) {
		return D(m - 1, n) + D(m - 1, n - 1) + D(m, n - 1);
	} else {
		int a, b, c;
#pragma omp task shared(a)
		a = D(m - 1, n);

#pragma omp task shared(b)
		b = D(m - 1, n - 1);

#pragma omp task shared(c)
		c = D(m, n - 1);

#pragma omp taskwait
		return a + b + c;
	}
}

int main(int argc, char** argv) {
	if(argc != 2) return 1;
	int n = atoi(argv[1]);
	int result = 0;

	double start_time = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp single
		{ result = D(n, n); }
	}
	double end_time = omp_get_wtime();
	printf("Elapsed time: %f seconds\n", end_time - start_time);
	printf("Result: %d", result);

	return 0;
}
