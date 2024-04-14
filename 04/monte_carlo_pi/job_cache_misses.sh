#!/bin/bash

# Define the number of threads to benchmark
threads=(12)
programs=("exercise02_v1" "exercise02_v2" "exercise02_v3" "exercise02_v3_1")

# Loop through each number of threads and run the benchmark
for p in "${programs[@]}"
do
    for t in "${threads[@]}"
    do
        echo "Benchmarking $p with $t threads..."
        perf stat -e LLC-load-misses -e LLC-store-misses ./$p $t
        echo "----------------------------------------------"
    done
done
