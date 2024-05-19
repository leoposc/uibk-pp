#!/bin/bash
# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

module load gcc/12.2.0-gcc-8.5.0-p4pe45v

# Compile the programs
make clean
make
make vectorized
make vectorized_optimized

# An array of problem sizes:
PROBLEM_SIZES=(100 2048 10000)

for SIZE in ${PROBLEM_SIZES[*]}; do
  echo "Running baseline with problem size: $SIZE"
  ./baseline $SIZE

  echo "Running vectorized with problem size: $SIZE"
  ./vectorized $SIZE

  echo "Running vectorized_optimized with problem size: $SIZE"
    ./vectorized_optimized $SIZE
done
