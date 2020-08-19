#SBATCH --time=00:02:00
#SBATCH --account=HOD
#SBATCH --ntasks-per-node 16
#SBATCH --nodes 4
#SBATCH -p ics632.q 


#export OMP_NUM_THREADS=16


# $1: Open-MP parallel mode
# $2: # of cores

mpirun  ./matmul_outerproduct_v1 -n $1






