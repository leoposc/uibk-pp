#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETITIONS 1000000 // Number of repetitions
#define EPSILON 0.0001f     // Tolerance for doubleing-point comparison

void initialize_vectors(double *a, double *b, double *c, int size) {
  for (int i = 0; i < size; ++i) {
    a[i] = 1.0f; // Initialize 'a' to 1.0
    b[i] = 2.0f; // Initialize 'b' to 2.0
    c[i] = 3.0f; // Initialize 'c' to 3.0
  }
}

bool verify_vector(double *a, int size, double expected_value) {
  for (int i = 0; i < size; ++i) {
    if ((a[i] < expected_value - EPSILON) ||
        (a[i] > expected_value + EPSILON)) {
      return false;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <size>\n", argv[0]);
    return 1;
  }

  int size = atoi(argv[1]);
  if (size <= 0) {
    fprintf(stderr, "Invalid input. Size must be a positive integer.\n");
    return 1;
  }
  // Allocate memory for the vectors
  double *a = (double *)malloc(size * sizeof(double));
  double *b = (double *)malloc(size * sizeof(double));
  double *c = (double *)malloc(size * sizeof(double));

  if (a == NULL || b == NULL || c == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return 1;
  }

  double expected_value =
      1.0f + (2.0f * 3.0f * REPETITIONS); // Calculate the expected value

  // Initialize the vectors
  initialize_vectors(a, b, c, size);

  // Measure the start time
  clock_t start_time = clock();

  // Perform the computation
  for (int run = 0; run < REPETITIONS; ++run) {
#pragma omp simd
    for (int i = 0; i < size; ++i) {
      a[i] += b[i] * c[i];
    }
  }

  // Measure the end time
  clock_t end_time = clock();

  // Calculate the elapsed time in seconds
  double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

  // Verify the resulting vector 'a'
  if (verify_vector(a, size, expected_value)) {
    printf("Computation is correct.\n");
  } else {
    printf("Computation is incorrect.\n");
  }

  // Print the elapsed time
  printf("Elapsed time: %f seconds\n", elapsed_time);

  // Free the allocated memory
  free(a);
  free(b);
  free(c);

  return 0;
}
