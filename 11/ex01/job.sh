#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name pp-exercise11
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=12
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

ts=(1 12)
ts=(1 2 6 12)

gcc *.c -lm -fopenmp

for t in ${ts[@]}; do
    echo "Running with $t threads"
    export OMP_NUM_THREADS=$t
    ./a.out
done

# gprof --line ./a.out gmon.out > analysis_parallel.txt