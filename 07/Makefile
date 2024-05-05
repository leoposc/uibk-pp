CC=gcc
C_FLAGS = -Wall -Wextra -Werror -std=c17 -pedantic -fopenmp -lm

.PHONY: all test build clean

TARGETS=exercise01 exercise03

all: $(TARGETS) test

test:
	@echo "Testing..."

clean:
	@echo "Cleaning..."
	@rm -rf $(TARGETS) *.o

../unity/unity.o:
	@echo "Building Unity..."
	@$(CC) -c ../unity/unity.c -o ../unity/unity.o

%: %.c ../unity/unity.o
	@echo "Building $@..."	
	@$(CC) $(C_FLAGS) $< ../unity/unity.o -o $@ 

