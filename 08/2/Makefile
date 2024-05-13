CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp
LDFLAGS = -lm -fopenmp
CC = gcc
RM = rm -f

.PHONY: all clean

all: hadamard_dynamic hadamard_guided hadamard_static hadamard_2 hadamard_auto hadamard_runtime hadamard_all

clean:
	$(RM) hadamard_dynamic hadamard_guided hadamard_static hadamard_2 hadamard_auto hadamard_runtime hadamard_all

hadamard_dynamic: hadamard_dynamic.c
	$(CC) $(CFLAGS) -o hadamard_dynamic hadamard_dynamic.c $(LDFLAGS)

hadamard_guided: hadamard_guided.c
	$(CC) $(CFLAGS) -o hadamard_guided hadamard_guided.c $(LDFLAGS)

hadamard_static: hadamard_static.c
	$(CC) $(CFLAGS) -o hadamard_static hadamard_static.c $(LDFLAGS)

hadamard_2: hadamard_2.c
	$(CC) $(CFLAGS) -o hadamard_2 hadamard_2.c $(LDFLAGS)

hadamard_auto: hadamard_auto.c
	$(CC) $(CFLAGS) -o hadamard_auto hadamard_auto.c $(LDFLAGS)

hadamard_runtime: hadamard_runtime.c
	$(CC) $(CFLAGS) -o hadamard_runtime hadamard_runtime.c $(LDFLAGS)

hadamard_all: hadamard_all.c
	$(CC) $(CFLAGS) -o hadamard_all hadamard_all.c $(LDFLAGS)
