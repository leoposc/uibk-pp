#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name pp-exercise09
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=12
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Define the number of threads to benchmark
ts=(1)
# ns=(6)
programs=("exercise01" "exercise01_vectorized")

# define the problem size:
ns=(128 512 1024 2048 4096 8192)

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
