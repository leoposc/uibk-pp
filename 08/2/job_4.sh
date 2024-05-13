#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name hadamard_benchmarks
# Redirect output stream to this file
#SBATCH --output=output.log
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

export OMP_SCHEDULE="dynmamic"

# Benchmark function
benchmark() {
    matrix_size=$1
    program=$2
    echo "Benchmarking program: $program with matrix size: $matrix_size"
    ./$program $matrix_size
}

# Loop over matrix sizes and programs
for size in "${sizes[@]}"
do
    for program in "hadamard_auto" "hadamard_runtime"
    do
        benchmark $size $program
        echo "----------------------------------------------"
        echo ""
    done
done

echo "All benchmarks completed."
