#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name atomic_increment
# Redirect output stream to this file
#SBATCH --output=output_2.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=64
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=8
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# Compilation
make clean
make

# Matrix sizes
sizes=(10000 20000 30000)

# Benchmark function
benchmark() {
    matrix_size=$1
    ./hadamard_2 $matrix_size
}

# Loop over matrix sizes
for size in "${sizes[@]}"
do
  benchmark $size
  echo "----------------------------------------------"
  echo ""
done

echo "All benchmarks completed."