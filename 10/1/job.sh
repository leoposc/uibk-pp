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

N=(5 9 10 11 12)


for SIZE in ${N[*]};
do
  echo "Computing sequential N: $SIZE"
  ./sequential "$SIZE"
  echo ""
  echo "Computing parallel N: $SIZE"
  ./parallel "$SIZE"
  echo ""
  echo ""
done
