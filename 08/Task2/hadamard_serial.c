#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hadamard_product_serial(int n, int **a, int **b, int **c) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      c[i][j] = a[i][j] * b[i][j];
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <matrix_size>\n", argv[0]);
    return 1;
  }

  int n = atoi(argv[1]);
  int **a = malloc(n * sizeof(int *));
  int **b = malloc(n * sizeof(int *));
  int **c = malloc(n * sizeof(int *));

  for (int i = 0; i < n; i++) {
    a[i] = (int *)malloc(sizeof(int) * n);
    b[i] = (int *)malloc(sizeof(int) * n);
    c[i] = (int *)malloc(sizeof(int) * n);
  }
  // Initialize matrices a and b
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a[i][j] = i + j;
      b[i][j] = i - j;
    }
  }

  clock_t start_time = clock(); // Start timing

  // Calculate Hadamard product serially
  hadamard_product_serial(n, a, b, c);

  clock_t end_time = clock(); // End timing

  // Print execution time
  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("Time taken (serial): %f seconds\n", elapsed_time);

  // Free memory for arrays a, b, and c
  for (int i = 0; i < n; ++i) {
    free(a[i]);
    free(b[i]);
    free(c[i]);
  }
  free(a);
  free(b);
  free(c);

  return 0;
}
