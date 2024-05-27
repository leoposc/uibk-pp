CC = gcc
CFLAGS = -std=c99 -Wall -O1 -fopenmp
SOURCES = heat_stencil_2D_parallel.c heat_stencil_2D_sequential.c
EXECUTABLES = heat_stencil_2D_parallel heat_stencil_2D_sequential

all: $(EXECUTABLES)

heat_stencil_2D_parallel: heat_stencil_2D_parallel.c
	$(CC) $(CFLAGS) -o heat_stencil_2D_parallel heat_stencil_2D_parallel.c

heat_stencil_2D_sequential: heat_stencil_2D_sequential.c
	$(CC) $(CFLAGS) -o heat_stencil_2D_sequential heat_stencil_2D_sequential.c

clean:
	rm -f $(EXECUTABLES)
