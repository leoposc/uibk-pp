#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Define the number of threads to benchmark
ns=(1500)
# ns=(100)
programs=("/ex1" "/ex1_improved")
# programs=("ex1/ex1_improved")
# Loop through each number of threads and run the benchmark
for p in "${programs[@]}"
do
    for n in "${ns[@]}"
    do
        echo "Benchmarking $p with $n as problem size..."
        ./$p $n
        echo "----------------------------------------------"
    done
done
