CC = gcc
CFLAGS_BASELINE = -std=c99 -Wall -O1
CFLAGS_VECTORIZED = -std=c99 -Wall -ftree-vectorize
CFLAGS_VECTORIZED_OPTIMIZED = -std=c99 -Wall -O2 -ftree-vectorize
SOURCES = sequential.c
EXECUTABLE = baseline
VECTOR_EXECUTABLE = vectorized
VECTOR_OPTIMIZED_EXECUTABLE = vectorized_optimized

baseline: $(SOURCES)
	$(CC) $(CFLAGS_BASELINE) -o $(EXECUTABLE) $(SOURCES)

vectorized: $(SOURCES)
	$(CC) $(CFLAGS_VECTORIZED) -o $(VECTOR_EXECUTABLE) $(SOURCES)

vectorized_optimized: $(SOURCES)
	$(CC) $(CFLAGS_VECTORIZED_OPTIMIZED) -o $(VECTOR_OPTIMIZED_EXECUTABLE) $(SOURCES)

# Default target to build both versions
all: baseline vectorized

# Clean up executables
clean:
	rm -f $(EXECUTABLE) $(VECTOR_EXECUTABLE) $(VECTOR_OPTIMIZED_EXECUTABLE)
