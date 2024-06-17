#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name parallel-13
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=12
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

rm a.out data.dat
echo "Compiling..."
g++ *.cpp -Wall -Wextra -Werror -O3 -fopenmp

# Define the number of threads to benchmark
ts=(1)

echo "Running..."
./a.out 

echo "Done!"