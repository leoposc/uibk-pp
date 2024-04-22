#include <omp.h>
#include <stdio.h>

int main() {
  int data, flag = 0;
#pragma omp parallel num_threads(2)
  {
    if (omp_get_thread_num() == 0) {

      data = 42;
      // Flush data to thread 1 and strictly order the write to data
      relative to the write to the flag * /
#pragma omp flush(flag, data)

          flag = 1;
      // Flush flag to ensure that thread 1 sees the change
#pragma omp flush(flag)

    } else if (omp_get_thread_num() == 1) {
      // Flush to read flag correctly
#pragma omp flush(flag, data)
      while (flag < 1) {
#pragma omp flush(flag, data)
      }
      // Flush, because access to both flag and data in print function
#pragma omp flush(flag, data)
      printf("flag=%d data=%d\n", flag, data);
    }
  }
  return 0;
}
