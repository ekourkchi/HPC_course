#!/bin/bash

#SBATCH -o slurm-%j.out-%N # name of the stdout, using the job number (%j) and the first node (%N)

# additional information for allocated clusters

#SBATCH -n 1        # 1 task
#SBATCH -c 7       # 1 core per task
#SBATCH -p ics632.q # Non-dedicated queue
export OMP_NUM_THREADS=7


./test_omp.x 



