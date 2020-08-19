#!/bin/bash

#SBATCH -o slurm-%j.out-%N # name of the stdout, using the job number (%j) and the first node (%N)
#SBATCH --time=100:00
#SBATCH -n 1       # number of tasks
#SBATCH -c 1       # number of cores per task
#SBATCH -N 1       # number of nodes
#SBATCH -p ics632.q # Non-dedicated queue

export OMP_NUM_THREADS=1


# $1: Open-MP parallel mode
# $2: # of cores

srun task.bash  0 0 






