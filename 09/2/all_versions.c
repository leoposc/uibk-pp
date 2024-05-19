#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define REPETITIONS 1000000
#define VALUE 1.0

void sequential_float(int size) {
	float* a = (float*)malloc(sizeof(float) * size);
	float* b = (float*)malloc(sizeof(float) * size);
	float* c = (float*)malloc(sizeof(float) * size);

	for(int i = 0; i < size; ++i) {
		a[i] = VALUE;
		b[i] = VALUE;
		c[i] = VALUE;
	}

	double start_time = omp_get_wtime();

	for(int run = 0; run < REPETITIONS; ++run) {
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}

	double end_time = omp_get_wtime();

	printf("Elapsed time: %f seconds\n", end_time - start_time);

	for(int i = 0; i < size && i < 10; ++i) {
		if(a[i] != REPETITIONS + 1) printf("Wrong result");
	}

	free(a);
	free(b);
	free(c);
}

void openmp_float(int size) {
	float* a = (float*)malloc(sizeof(float) * size);
	float* b = (float*)malloc(sizeof(float) * size);
	float* c = (float*)malloc(sizeof(float) * size);


	for(int i = 0; i < size; ++i) {
		a[i] = VALUE;
		b[i] = VALUE;
		c[i] = VALUE;
	}
	double start_time = omp_get_wtime();

	for(int run = 0; run < REPETITIONS; ++run) {
#pragma omp simd
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}

	double end_time = omp_get_wtime();

	printf("Elapsed time: %f seconds\n", end_time - start_time);

	for(int i = 0; i < size && i < 10; ++i) {
		if(a[i] != REPETITIONS + 1) printf("Wrong result");
	}

	free(a);
	free(b);
	free(c);
}

void sequential_double(int size) {
	double* a = (double*)malloc(sizeof(double) * size);
	double* b = (double*)malloc(sizeof(double) * size);
	double* c = (double*)malloc(sizeof(double) * size);


	for(int i = 0; i < size; ++i) {
		a[i] = VALUE;
		b[i] = VALUE;
		c[i] = VALUE;
	}
	double start_time = omp_get_wtime();

	for(int run = 0; run < REPETITIONS; ++run) {
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}

	double end_time = omp_get_wtime();

	printf("Elapsed time: %f seconds\n", end_time - start_time);

	for(int i = 0; i < size && i < 10; ++i) {
		if(a[i] != REPETITIONS + 1) printf("Wrong result");
	}

	free(a);
	free(b);
	free(c);
}

void openmp_double(int size) {
	double* a = (double*)malloc(sizeof(double) * size);
	double* b = (double*)malloc(sizeof(double) * size);
	double* c = (double*)malloc(sizeof(double) * size);


	for(int i = 0; i < size; ++i) {
		a[i] = VALUE;
		b[i] = VALUE;
		c[i] = VALUE;
	}
	double start_time = omp_get_wtime();

	for(int run = 0; run < REPETITIONS; ++run) {
#pragma omp simd
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}

	double end_time = omp_get_wtime();

	printf("Elapsed time: %f seconds\n", end_time - start_time);

	for(int i = 0; i < size && i < 10; ++i) {
		if(a[i] != REPETITIONS + 1) printf("Wrong result");
	}

	free(a);
	free(b);
	free(c);
}

int main(int argc, char** argv) {
	if(argc != 2) return 1;
	int size = atoi(argv[1]);

	printf("Sequential execution with float:");
	sequential_float(size);

	printf("\nOpenMP execution with float:");
	openmp_float(size);

	printf("\nSequential execution with double:");
	sequential_double(size);

	printf("\nOpenMP execution with double:");
	openmp_double(size);

	return 0;
}
