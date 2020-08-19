#!/bin/bash
 
#SBATCH -o size-3040-iter-%a-%N.txt
#SBATCH --time=00:00:30
#SBATCH --account=HOD
#SBATCH --ntasks-per-node 16
#SBATCH --nodes 4


#export OMP_NUM_THREADS=16


# $1: Open-MP parallel mode
# $2: # of cores

srun ./matmul_outerproduct_v1 -s $1






