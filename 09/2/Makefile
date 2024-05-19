CC = gcc
CFLAGS = -std=c99 -Wall -O1 -fopenmp
CFLAGS_VECTOR_OPTIMIZATION = -std=c99 -Wall -O2 -ftree-vectorize
SOURCES = all_versions.c openmp_float.c sequential.c
EXECUTABLE = all_versions openmp_float sequential sequential_optimized

all: $(EXECUTABLE)

all_versions: all_versions.c
	$(CC) $(CFLAGS) -o all_versions all_versions.c

openmp_float: openmp_float.c
	$(CC) $(CFLAGS) -o openmp_float openmp_float.c

sequential: sequential.c
	$(CC) $(CFLAGS) -o sequential sequential.c

sequential_optimized: sequential.c
	$(CC) $(CFLAGS_VECTOR_OPTIMIZATION) -o sequential_optimized sequential.c

clean:
	rm -f $(EXECUTABLE)
