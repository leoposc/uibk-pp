CC=gcc
C_FLAGS = -Wall -Wextra -Werror -std=c17 -pedantic -O3 -g


# Find all .c files in the current directory
SRC = $(wildcard *.c)

# Generate the list of executables by replacing the .c extension with nothing
EXE = $(SRC:.c=)

# Default target
all: $(EXE)

# Rule to build each executable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove all executables
clean:
	rm -f $(EXE)
