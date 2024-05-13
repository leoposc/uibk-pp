CC=gcc
C_FLAGS = -Wall -Wextra -Werror -std=c17 -fopenmp -O3

.PHONY: all
all: hadamard_serial hadamard_par

.PHONY: clean
clean:
	$(RM) hadamard_serial hadamard_par

hadamard_serial: hadamard_serial.c

hadamard_par:hadamard_par.c