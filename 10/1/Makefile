CC = gcc
CFLAGS = -std=c99 -Wall -O1 -fopenmp
SOURCES = sequential.c
EXECUTABLE = sequential

all: $(EXECUTABLE)

sequential: sequential.c
	$(CC) $(CFLAGS) -o sequential sequential.c

clean:
	rm -f $(EXECUTABLE)