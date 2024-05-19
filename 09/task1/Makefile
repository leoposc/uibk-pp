# Makefile for compiling the vector computation program with auto-vectorization

CC = gcc
CFLAGS = -O1 -Wall -Wextra -Werror -std=c11 -ftree-vectorize -ftree-loop-vectorize

# Target executable
TARGET = vectorization

# Source files
SRCS = vectorization.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
