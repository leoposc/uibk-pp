#!/bin/bash

#SBATCH --partition=lva
#SBATCH --job-name vectorization_intrinsic
#SBATCH --output=output.log
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive

# Array of sizes
sizes=(16 32 64 128 256 512 1024 2048)

# Execute the program for each size
for size in "${sizes[@]}"; do
    echo "Running vectorization_intrinsic with size $size"
    ./vectorization_intrinsic $size
done


echo "Running vectorization_intrinsic with size $size"
perf stat -e r1001 ./vectorization_intrinsic 2048
perf stat -e r1002 ./vectorization_intrinsic 2048
perf stat -e r1004 ./vectorization_intrinsic 2048
perf stat -e r1008 ./vectorization_intrinsic 2048
perf stat -e r1010 ./vectorization_intrinsic 2048
perf stat -e r1020 ./vectorization_intrinsic 2048
perf stat -e r1040 ./vectorization_intrinsic 2048
perf stat -e r1080 ./vectorization_intrinsic 2048