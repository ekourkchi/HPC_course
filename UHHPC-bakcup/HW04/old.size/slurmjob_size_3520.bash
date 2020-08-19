#!/bin/bash
 
#SBATCH -o size-3520-iter-%a-%N.txt
#SBATCH --time=00:00:30
#SBATCH -n 1       # number of tasks
#SBATCH -c 16       # number of cores per task
#SBATCH -N 4       # number of nodes
#SBATCH -p ics632.q # Non-dedicated queue

export OMP_NUM_THREADS=16


# $1: Open-MP parallel mode
# $2: # of cores

mpirun -np 64 ./matmul_outerproduct_v1 -n $1







