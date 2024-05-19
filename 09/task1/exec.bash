#!/bin/bash

# Array of sizes
sizes=(16 32 64 128 256 512 1024 2048)

# Execute the program for each size
for size in "${sizes[@]}"; do
    echo "Running vectorization with size $size"
    ./vectorization $size
done

echo "Running vectorization with size $size"
perf stat -e rYYXX ./vectorization 2048