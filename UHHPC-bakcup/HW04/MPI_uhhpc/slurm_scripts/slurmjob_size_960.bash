#!/bin/bash
 
#SBATCH -o size-960-iter-%a-%N.txt
#SBATCH --time=00:02:00
#SBATCH -p ics632.q # Non-dedicated queue
#SBATCH --ntasks-per-node 16
#SBATCH --nodes 4

# export OMP_NUM_THREADS=16


# $1: Open-MP parallel mode
# $2: # of cores

mpirun  ./matmul_outerproduct_v1 -n $1







