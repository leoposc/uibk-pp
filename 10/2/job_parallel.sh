#!/bin/bash
# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name exercise07
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

make clean
make

size=(125 250 500)
ns=(1 2 4 8 12)

for s in "${size[@]}"
do
    echo "Benchmarking sequential with size $s:"
      ./heat_stencil_2D_sequential $s
    echo "----------------------------------------------"
    echo ;

    for n in "${ns[@]}"
    do
        echo "Benchmarking parallel with $n threads, size $s"

        export OMP_NUM_THREADS=$n
        ./heat_stencil_2D_parallel $s
        echo "----------------------------------------------"
        echo ;
    done
done