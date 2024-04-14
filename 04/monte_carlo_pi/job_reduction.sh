#!/bin/bash

# Define the number of threads to benchmark
threads=(1 2 4 6 12)

# Loop through each number of threads and run the benchmark
for t in "${threads[@]}"
do
    echo "Benchmarking mc_pi_reduction with $t threads..."
    export OMP_NUM_THREADS=$t
    time ./mc_pi_reduction
    echo "----------------------------------------------"
done
