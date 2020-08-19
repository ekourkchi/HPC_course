#!/bin/bash
#SBATCH --time=1:00:00 # walltime, abbreviated by -t
#SBATCH --nodes=1      # number of cluster nodes, abbreviated by -N
#SBATCH -o slurm-%j.out-%N # name of the stdout, using the job number (%j) and the first node (%N)
#SBATCH --ntasks=1    # number of MPI tasks, abbreviated by -n
# additional information for allocated clusters


#SBATCH -n 1 # 1 task
#SBATCH -c 1 # 1 core per task
#SBATCH -N 1 # 1 node
#SBATCH -p ics632.q # Non-dedicated queue

./task.bash  $SLURM_ARRAY_TASK_ID


