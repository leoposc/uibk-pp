#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IND(i, j) ((i) * (n) + (j))

int main(int argc, char **argv) {
	// handle input
	if (argc != 2) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	errno = 0;
	char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0) {
		fprintf(stderr, "Error: matrix size must not be negative!\n");
		return EXIT_FAILURE;
	}

	// allocate memory
	int status = EXIT_FAILURE;
	int *a = malloc(n * n * sizeof(int));
	int *b = malloc(n * n * sizeof(int));
    int *c = malloc(n * n * sizeof(int));
    status = EXIT_SUCCESS;

	unsigned long res = 0;

	// fill matrix
	srand(7);
	for (long i = 0; i < n; ++i) {
		for (long j = 0; j < n; ++j) {
			a[IND(i, j)] = rand();
			b[IND(i, j)] = rand();
		}
	}

	double start_time = omp_get_wtime();

		// matrix multiplication
#pragma omp parallel for default(none) shared(n, a, b, c)
		for (long i = 0; i < n; ++i) {
			for (long j = 0; j < n; ++j) {
				for (long k = 0; k < n; ++k) {
					c[IND(i, j)] += a[IND(i, k)] * b[IND(k, j)];
				}
			}
		}

#pragma omp parallel for reduction (+: res)
		for (long i = 0; i < n * n; ++i) {
			res += c[i];
		}

	double end_time = omp_get_wtime();
	printf("$!%s: %2.2f seconds, res: %lu\n", argv[0], end_time - start_time, res);

// 	// cleanup
	free(c);
	free(b);
	free(a);
	return status;
}