CFLAGS = -std=gnu11 -Wall -Wextra -lm

.PHONY: all
TARGET1 = hadamard_slow
TARGET2 = hadamard_fast
TARGET3 = cache_misses_calculation

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(TARGET1).o
	$(CC) $(CFLAGS) -o $@ $^
$(TARGET1).o: $(TARGET1).c
	$(CC) $(CFLAGS) -c -o $@ $^

$(TARGET2): $(TARGET2).o
	$(CC) $(CFLAGS) -o $@ $^
$(TARGET2).o: $(TARGET2).c
	$(CC) $(CFLAGS) -c -o $@ $^

$(TARGET3): $(TARGET3).o
	$(CC) $(CFLAGS) -o $@ $^
$(TARGET3).o: $(TARGET3).c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) *.o $(TARGET1)
	$(RM) *.o $(TARGET2)
	$(RM) *.o $(TARGET3)
