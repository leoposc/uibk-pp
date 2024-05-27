CC = gcc
CFLAGS = -std=c99 -Wall -O1 -fopenmp
SOURCES = sequential.c parallel.c
EXECUTABLES = sequential parallel

all: $(EXECUTABLES)

sequential: sequential.c
	$(CC) $(CFLAGS) -o sequential sequential.c

parallel: parallel.c
	$(CC) $(CFLAGS) -o parallel parallel.c

clean:
	rm -f $(EXECUTABLES)
