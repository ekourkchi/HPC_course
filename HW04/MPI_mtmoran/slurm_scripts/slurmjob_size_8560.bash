#!/bin/bash
 
#SBATCH -o size-8560-iter-%a-%N.txt
#SBATCH --time=00:02:00
#SBATCH --account=HOD
#SBATCH --ntasks-per-node 16
#SBATCH --nodes 4


#export OMP_NUM_THREADS=16


# $1: Open-MP parallel mode
# $2: # of cores

srun ./matmul_outerproduct_v1 -s $1






