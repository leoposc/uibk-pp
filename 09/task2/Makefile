CC = gcc
CFLAGS = -O1 -Wall -Wextra -Werror -std=c11 -fopenmp 
.PHONY: all
all: vectorization_omp vectorization_omp_double

.PHONY: clean
clean:
	$(RM) vectorization_omp vectorization_omp_double

vectorization_omp: vectorization_omp.c

vectorization_omp_double:vectorization_omp_double.c