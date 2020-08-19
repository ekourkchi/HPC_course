#!/bin/bash
 
#SBATCH -o size-4960-iter-%a-%N.omp.txt
#SBATCH --time=00:02:00
#SBATCH --account=HOD
#SBATCH --ntasks-per-node 1
#SBATCH --nodes 4
#SBATCH --cpus-per-task 16    # -c


# it equals to --cpus-per-task
export OMP_NUM_THREADS=16



srun ./matmul_outerproduct_v1_omp -n $1






