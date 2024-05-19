CC=gcc
C_FLAGS = -Wall -Wextra -Werror -std=c17 -pedantic -fopenmp -O1 
# -ftree-vectorize -ftree-vectorizer-verbose=2

.PHONY: all test build clean

TARGETS=exercise01 exercise01_vectorized
all: $(TARGETS) 

clean:
	@echo "Cleaning..."
	@rm -rf $(TARGETS) *.o

%: %.c
	@echo "Building $@..."	
	@$(CC) $(C_FLAGS) $< -o $@ 

