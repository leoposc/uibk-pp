#!/bin/bash

# Define the number of threads to benchmark
threads=(1 2 4 6 12)

# Loop through each number of threads and run the benchmark
for t in "${threads[@]}"
do
    echo "Benchmarking mc_pi_atomic with $t threads..."
    time ./mc_pi_atomic $t
    echo "----------------------------------------------"
done
