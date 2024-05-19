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
module load perf

make clean
make vectorized
make vectorized_optimized

PROBLEM_SIZES=(1000)

# Event codes for vectorized instructions
EVENTS=(
    r1010 # FP_COMP_OPS_EXE.SSE_FP_PACKED
    r1020 # FP_COMP_OPS_EXE.SSE_FP_SCALAR
    r1040 # FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION
)

for SIZE in ${PROBLEM_SIZES[*]}; do

  echo "Profiling vectorized with perf for size: $SIZE"
  for EVENT in ${EVENTS[*]}; do
    echo "Event $EVENT"
    perf stat -e $EVENT ./vectorized $SIZE 2>> vectorized_perf_$SIZE.log
  done

  echo "Profiling vectorized_optimized with perf for size: $SIZE"
  for EVENT in ${EVENTS[*]}; do
    echo "Event $EVENT"
    perf stat -e $EVENT ./vectorized_optimized $SIZE 2>> vectorized_optimized_perf_$SIZE.log
  done
done
