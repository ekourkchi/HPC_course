#!/bin/sh

module purge
module load intel/ics intel/impi
. /opt/intel/composerxe/mkl/bin/mklvars.sh intel64
mpiicc -o hello_mpi.intel hello_mpi.c

export I_MPI_PMI_LIBRARY=/opt/local/slurm/default/lib64/libpmi.so

srun -n 40 ./hello_mpi.intel >> hello_mpi.out 2>&1

