#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name exercise08
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=6
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=6
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Define the number of threads to benchmark
# ns=(1 2 4 6 12)
ns=(6)
programs=("exercise01")

# Loop through each number of threads and run the benchmark
for p in "${programs[@]}"
do
    for n in "${ns[@]}"
    do
              echo "Benchmarking $p with $n threads..."
        export OMP_NUM_THREADS=$n
        export OMP_PROC_BIND=master
        export OMP_PLACES=threads
        ./$p 
        echo "----------------------------------------------"
        echo ;

        echo "Benchmarking $p with $n threads..."
        export OMP_NUM_THREADS=$n
        export OMP_PROC_BIND=spread
        export OMP_PLACES=sockets
        ./$p 
        echo "----------------------------------------------"
        echo ;

        echo "Benchmarking $p with $n threads..."
        export OMP_NUM_THREADS=$n
        export OMP_PROC_BIND=close
        export OMP_PLACES=threads
        ./$p 
        echo "----------------------------------------------"
        echo ;
    done
done
