CC=g++
C_FLAGS = -O3 -fopenmp

.PHONY: all test build clean

TARGETS=heat_stencil_2D heat_stencil_2D_parallel delannoy_sequential delannoy_parallel
all: $(TARGETS) 

clean:
	@echo "Cleaning..."
	@rm -rf $(TARGETS) *.o

%: %.cpp
	@echo "Building $@..."
	@$(CC) $(C_FLAGS) $< -o $@ -fopenmp
