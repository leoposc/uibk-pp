#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output2.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Define the number of threads to benchmark
threads=(12)
programs=("exercise02_v1" "exercise02_v2" "exercise02_v3" "exercise02_v3_1")

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
