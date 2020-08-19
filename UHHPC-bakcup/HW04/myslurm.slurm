#!/bin/bash

#SBATCH -o size-${1}-iter-%a-%N.txt # name of the stdout, using the job number (%j) and the first node (%N) and (%a is taks ID)
#SBATCH --time=00:00:30
#SBATCH -n 1       # number of tasks
#SBATCH -c 16       # number of cores per task
#SBATCH -N 1       # number of nodes
##SBATCH -p ics632.q # Non-dedicated queue

export OMP_NUM_THREADS=16


# $1: Open-MP parallel mode
# $2: # of cores

mpirun -np 16 ./matmul_outerproduct_v1 -n 3200







