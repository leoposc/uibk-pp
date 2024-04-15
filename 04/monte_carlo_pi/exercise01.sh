#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output2.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive


# Define the number of threads to benchmark
threads=(1 2 4 6 12)
programs=("mc_pi_atomic" "mc_pi_critical" "mc_pi_reduction" "mc_pi_pthreads")
# programs=("mc_pi_critical" )
# Loop through each number of threads and run the benchmark
for p in "${programs[@]}"
do
    for t in "${threads[@]}"
    do
        echo "Benchmarking $p with $t threads..."
        ./$p $t
        echo "----------------------------------------------"
    done
done
