CC = gcc
CFLAGS = -std=c99 -Wall -O1 -fopenmp
CFLAGS_VECTOR_OPTIMIZATION = -std=c99 -Wall -O2 -ftree-vectorize
SOURCES = openmp_float.c sequential.c exercise03.c
EXECUTABLE = openmp_float sequential sequential_optimized exercise03

all: $(EXECUTABLE)

exercise03: exercise03.c
	$(CC) $(CFLAGS) -o exercise03 exercise03.c

openmp_float: openmp_float.c
	$(CC) $(CFLAGS) -o openmp_float openmp_float.c

sequential: sequential.c
	$(CC) $(CFLAGS) -o sequential sequential.c

sequential_optimized: sequential.c
	$(CC) $(CFLAGS_VECTOR_OPTIMIZATION) -o sequential_optimized sequential.c

clean:
	rm -f $(EXECUTABLE)
