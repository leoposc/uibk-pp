#!/bin/bash

# Define the number of threads to benchmark
threads=(1 2 4 6 12)
programs=("mc_pi_atomic" "mc_pi_critical" "mc_pi_reduction" "mc_pi_pthreads")

# Loop through each number of threads and run the benchmark
for p in "${programs[@]}"
do
    for t in "${threads[@]}"
    do
        echo "Benchmarking $p with $t threads..."
        time ./$p $t
        echo "----------------------------------------------"
    done
done
