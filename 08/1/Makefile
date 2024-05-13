CC = gcc
CFLAGS = -fopenmp -O3
TARGET = atomic_increment
SRCS = atomic_increment.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
