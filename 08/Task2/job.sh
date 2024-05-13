#!/bin/bash

#SBATCH --partition=lva
#SBATCH --job-name hadamard
#SBATCH --output=output.log
#SBATCH --ntasks=12
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive
make
# Matrix sizes
sizes=(10000 20000 30000)

# Number of threads
threads=(1 2 4 6 12)

# Scheduling options
schedules=("static" "dynamic" "guided")

# Program names
hadamard_par="./hadamard_par"
hadamard_serial="./hadamard_serial"

# Loop over matrix sizes
for size in "${sizes[@]}"; do
    echo "Matrix size: $size"
    for schedule in "${schedules[@]}"; do
        echo "Scheduling type: $schedule"
        for thread in "${threads[@]}"; do
            echo "Number of threads: $thread"
            export OMP_NUM_THREADS=$thread
            $hadamard_par $size $schedule
            echo "----------------------------------------"
        done
    done
    echo "Executing program without schedule for matrix size $size"
    $hadamard_serial $size
    echo "----------------------------------------"
done
make clean