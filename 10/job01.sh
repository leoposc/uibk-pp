#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name pp-exercise10
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=12
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Define the number of threads to benchmark
ts=(12)
# ns=(6)
programs=("delannoy_parallel" "delannoy_sequential")
programs=("delannoy_parallel")

# define the problem size:
ns=(3 8 12)

# Loop through each number of threads and run the benchmark
for p in "${programs[@]}"
do
    for t in "${ts[@]}"
    do
        for n in "${ns[@]}"
        do
            echo "Benchmarking $p (problem size: $n) with $t threads..."
            export OMP_NUM_THREADS=$t
            ./$p $n
            echo "----------------------------------------------"
            echo ;
        done
    done
done
