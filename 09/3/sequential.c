#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETITIONS 1e6
#define VALUE 1.0f

int main(int argc, char** argv) {
	if(argc != 2) return 1;
	int size = atoi(argv[1]);

	float* a = (float*)malloc(sizeof(float) * size);
	float* b = (float*)malloc(sizeof(float) * size);
	float* c = (float*)malloc(sizeof(float) * size);

	for(int i = 0; i < size; ++i) {
		a[i] = VALUE;
		b[i] = VALUE;
		c[i] = VALUE;
	}

	clock_t start_time = clock();

	for(int run = 0; run < REPETITIONS; ++run) {
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}

	clock_t end_time = clock();

	double computation_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("Computation took %f seconds:   ", computation_time);

	int correct = 1;
	for(int i = 0; i < size; ++i) {
		if(a[i] != REPETITIONS + 1.0f) {
			correct = 0;
			break;
		}
	}
	if(correct) {
		printf("Result is correct.\n");
	} else {
		printf("Result is incorrect.\n");
	}

	free(a);
	free(b);
	free(c);

	return 0;
}