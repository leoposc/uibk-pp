CC = gcc-12.2.0
CFLAGS = -Wall -Wextra -fopenmp -O3

PROGRAM = atomic_increment

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).c
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f $(PROGRAM)
