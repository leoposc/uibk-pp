#include <omp.h>
#include <stdio.h>
#include <time.h>

#define NUM_THREADS 6
#define NUM_ITERATIONS 500000000

int main() {
  int counter = 0;
  double start_time, end_time;

  omp_set_num_threads(NUM_THREADS);

  start_time = omp_get_wtime();

#pragma omp parallel for
  for (int i = 0; i < NUM_ITERATIONS; i++) {
#pragma omp atomic
    counter++;
  }

  end_time = omp_get_wtime();

  printf("Time taken: %f seconds\n", end_time - start_time);

  return 0;
}
