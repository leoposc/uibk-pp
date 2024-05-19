#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name exercise08
# Redirect output stream to this file
#SBATCH --output=65536.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=12
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Define the number of threads to benchmark
ts=(1 2 4 6 12)
ts=(12)
# ns=(6)
programs=("hadamard_p_static" "hadamard_p_dynamic" "hadamard_p_guided")
programs=("hadamard_p_static")
# define the problem size:
ns=(10000 20000 30000)
ns=(65536)
ns=(1000)
# ns=(2000000)

# export OMP_PROC_BIND=master
# export OMP_PLACES=threads

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
