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
make openmp_float
make sequential
make sequential_optimized

PROBLEM_SIZES=(2048)

EVENTS=(
    r1010 # FP_COMP_OPS_EXE.SSE_FP_PACKED
    r1020 # FP_COMP_OPS_EXE.SSE_FP_SCALAR
    r1040 # FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION
)

for SIZE in ${PROBLEM_SIZES[*]}; do
  echo "Profiling open mp float with perf for size: $SIZE"
  for EVENT in ${EVENTS[*]}; do
    echo "Event $EVENT"
    perf stat -e $EVENT ./openmp_float $SIZE >> openmp_float_perf_$SIZE.log 2>&1
    echo ""
  done

  echo "Profiling sequential float with perf for size: $SIZE"
    for EVENT in ${EVENTS[*]}; do
      echo "Event $EVENT"
      perf stat -e $EVENT ./sequential $SIZE >> sequential_perf_$SIZE.log 2>&1
      echo ""
    done

  echo "Profiling vector_compiler_optimized float with perf for size: $SIZE"
  for EVENT in ${EVENTS[*]}; do
    echo "Event $EVENT"
    perf stat -e $EVENT ./sequential_optimized $SIZE >> sequential_optimized_perf_$SIZE.log 2>&1
    echo ""
  done
done
