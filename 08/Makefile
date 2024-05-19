CC=gcc
C_FLAGS = -Wall -Wextra -Werror -std=c17 -pedantic -fopenmp -O3

.PHONY: all test build clean

TARGETS=exercise01 hadamard_p_static hadamard_serial hadamard_p_dynamic hadamard_p_guided hadamard_p_auto hadamard_p_runtime
all: $(TARGETS) 

clean:
	@echo "Cleaning..."
	@rm -rf $(TARGETS) *.o

%: %.c
	@echo "Building $@..."	
	@$(CC) $(C_FLAGS) $< -o $@ 

