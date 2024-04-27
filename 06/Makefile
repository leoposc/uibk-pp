CC=gcc
C_FLAGS = -Wall -Wextra -Werror -std=c17 -pedantic -fopenmp

.PHONY: all test build clean

TARGETS=main

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

