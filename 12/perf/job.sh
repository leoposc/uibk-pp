#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name pp-exercise11
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=12
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive


perf stat ./a -e cache-misses,cache-references,instructions,cycles > a.log
perf stat ./a_optimized -e cache-misses,cache-references,instructions,cycles > a_optimized.log 
perf stat ./b -e cache-misses,cache-references,instructions,cycles > b.log
perf stat ./b_optimized -e cache-misses,cache-references,instructions,cycles  > b_optimized.log
perf stat ./c -e cache-misses,cache-references,instructions,cycles > c.log
perf stat ./c_optimized -e cache-misses,cache-references,instructions,cycles > c_optimized.log
perf report 