#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void parallel_hadamard_product_auto(int_fast8_t** a, int_fast8_t** b, int_fast8_t** c, size_t n) {
#pragma omp parallel for schedule(auto) collapse(2)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}
}

void parallel_hadamard_product_dynamic(int_fast8_t** a, int_fast8_t** b, int_fast8_t** c, size_t n) {
#pragma omp parallel for schedule(dynamic, 8) collapse(2)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}
}

void parallel_hadamard_product_guided(int_fast8_t** a, int_fast8_t** b, int_fast8_t** c, size_t n) {
#pragma omp parallel for schedule(guided, 4) collapse(2)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}
}

void parallel_hadamard_product_runtime(int_fast8_t** a, int_fast8_t** b, int_fast8_t** c, size_t n) {
#pragma omp parallel for schedule(runtime) collapse(2)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}
}

void parallel_hadamard_product_static(int_fast8_t** a, int_fast8_t** b, int_fast8_t** c, size_t n) {
#pragma omp parallel for schedule(static) collapse(2)
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
	int_fast8_t ** a = (int_fast8_t**)malloc(n * sizeof(int_fast8_t*));
	int_fast8_t** b = (int_fast8_t**)malloc(n * sizeof(int_fast8_t*));
	int_fast8_t** c = (int_fast8_t**)malloc(n * sizeof(int_fast8_t*));

	omp_set_num_threads(64);

	#pragma omp for schedule(guided, 4)
	for(size_t i = 0; i < n; ++i) {
		a[i] = (int_fast8_t*)malloc(n * sizeof(int_fast8_t));
		b[i] = (int_fast8_t*)malloc(n * sizeof(int_fast8_t));
		c[i] = (int_fast8_t*)malloc(n * sizeof(int_fast8_t));
	}

	printf("Malloc done\n");

	#pragma omp for schedule(guided, 4) collapse(2)
	for(size_t i = 0; i < n; ++i) {
		for(size_t j = 0; j < n; ++j) {
			a[i][j] = 1.0;
			b[i][j] = 2.0;
		}
	}

	printf("Init done\n");

	omp_sched_t schedule_type;
	int chunk_size;
	char* schedule_str;

	omp_get_schedule(&schedule_type, &chunk_size);
	switch(schedule_type) {
		case omp_sched_static:
			schedule_str = "static";
			break;
		case omp_sched_dynamic:
			schedule_str = "dynamic";
			break;
		case omp_sched_guided:
			schedule_str = "guided";
			break;
		case omp_sched_auto:
			schedule_str = "auto";
			break;
		default:
			schedule_str = "unknown";
			break;
	}
	printf("OMP_SCHEDULE: %s\n", schedule_str);
	printf("Chunk size: %d\n", chunk_size);

	int num_threads[] = {12};

	for(int i = 0; i < 1; ++i) {
		omp_set_num_threads(num_threads[i]);

		//dynamic
		double start_time = omp_get_wtime();
		parallel_hadamard_product_dynamic(a, b, c, n);
		double end_time = omp_get_wtime();
		printf("dynamic: %zu n, %d threads, parallel, time: %f seconds \n", n, num_threads[i],
		       end_time - start_time);

		//guided
		start_time = omp_get_wtime();
		parallel_hadamard_product_guided(a, b, c, n);
		end_time = omp_get_wtime();
		printf("guided: %zu n, %d threads, parallel, time: %f seconds \n", n, num_threads[i],
		       end_time - start_time);

		//static
		start_time = omp_get_wtime();
		parallel_hadamard_product_static(a, b, c, n);
		end_time = omp_get_wtime();
		printf("static: %zu n, %d threads, parallel, time: %f seconds \n", n, num_threads[i],
		       end_time - start_time);

		//auto
		start_time = omp_get_wtime();
		parallel_hadamard_product_auto(a, b, c, n);
		end_time = omp_get_wtime();
		printf("auto: %zu n, %d threads, parallel, time: %f seconds \n", n, num_threads[i],
		       end_time - start_time);

		//runtime
		start_time = omp_get_wtime();
		parallel_hadamard_product_runtime(a, b, c, n);
		end_time = omp_get_wtime();
		printf("runtime: %zu n, %d threads, parallel, time: %f seconds \n", n, num_threads[i],
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
