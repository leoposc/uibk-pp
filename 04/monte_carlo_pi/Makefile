CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c17 -O3 -march=native -g -fopenmp
LDFLAGS=-lpthread

TARGETS=mc_pi_pthreads mc_pi_critical mc_pi_atomic mc_pi_reduction exercise02_v1 exercise02_v2 exercise02_v3 exercise02_v3_1

.PHONY: all clean

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)


%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
