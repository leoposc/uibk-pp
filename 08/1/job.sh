#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name atomic_increment
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=6
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

export OMP_NUM_THREADS=6

affinity_settings=("master" "close" "spread")

# Loop through each affinity setting
for setting in "${affinity_settings[@]}"
do
    echo "Affinity Setting: OMP_PROC_BIND= $setting"

    export OMP_PROC_BIND=$setting

    ./atomic_increment

    echo "============================="
done