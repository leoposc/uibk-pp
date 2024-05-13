#!/bin/bash

#SBATCH --partition=lva
#SBATCH --job-name atomic_increment
#SBATCH --output=output.log
#SBATCH --ntasks=6
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive
make
affinity_settings=(
    "OMP_PROC_BIND=close" 
    "OMP_PROC_BIND=spread" 
    "OMP_PROC_BIND=master" 
)

# OMP_PLACES settings
places_settings=(
    "OMP_PLACES=sockets" 
    "OMP_PLACES=cores" 
    "OMP_PLACES=threads" 
)

# Compile the program
gcc -o atomic_increment atomic_increment.c -fopenmp

# Run the program with different affinity settings
for bind_setting in "${affinity_settings[@]}"; do
    for places_setting in "${places_settings[@]}"; do
        echo "Running with affinity settings: $bind_setting $places_setting"
        export $bind_setting
        export $places_setting
        ./atomic_increment
        echo ""
    done
done
make clean