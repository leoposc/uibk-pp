#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void hadamard_product(int n, int a[n][n], int b[n][n], int c[n][n],
                      char *schedule_type) {
  int i, j;
#pragma omp parallel for schedule(runtime)
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      c[i][j] = a[i][j] * b[i][j];
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <matrix_size> <schedule_type>\n", argv[0]);
    printf("Available scheduling types: static, dynamic, guided\n");
    return 1;
  }

  int n = atoi(argv[1]);
  char *schedule_type = argv[2];
  int a[n][n], b[n][n], c[n][n];

  // Initialize matrices a and b
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a[i][j] = i + j;
      b[i][j] = i - j;
    }
  }

  // Set schedule type
  omp_set_schedule(omp_sched_dynamic, 0);

  double start_time = omp_get_wtime();

  // Calculate Hadamard product with specified scheduling type
  switch (schedule_type[0]) {
  case 's':
    omp_set_schedule(omp_sched_static, 0);
    break;
  case 'd':
    omp_set_schedule(omp_sched_dynamic, 0);
    break;
  case 'g':
    omp_set_schedule(omp_sched_guided, 0);
    break;
  default:
    printf("Invalid scheduling type\n");
    return 1;
  }

  hadamard_product(n, a, b, c, schedule_type);

  double end_time = omp_get_wtime(); // End timing

  // Print execution time
  printf("Time taken (%s): %f seconds\n", schedule_type, end_time - start_time);

  return 0;
}
