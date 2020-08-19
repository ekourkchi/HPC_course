#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

# include <omp.h>
#include <mpi.h>

// compile: <for simulation>
// smpicc check_mpi_omp.c -o check_mpi_omp.x -O4 -fopenmp -lm
// smpirun --cfg=smpi/bcast:mpich --cfg=smpi/running_power:0.047 -np 4 -platform cluster_1600.xml -hostfile hostfile_1600.bin ./check_mpi_omp.x

// export OMP_NUM_THREADS=16
// where 16 is the total number of threads


int main(int argc, char *argv[])
{
  
  int iam=0, np=1;
    
  MPI_Init(&argc, &argv);
  
  // Determine rank and number of processes
  int num_procs;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  
  
  printf("Hello World. I am MPI rank # %d of %d\n", rank, num_procs);
   
   
  #pragma omp parallel private(iam, np)
  {
    np =  omp_get_num_threads();  // Total number of threads
    iam = omp_get_thread_num();  // Current thread number
    printf("Hello from thread %d out of %d threads, MPI_rank: %d\n", iam, np, rank);
  }
 
  
  
  
return(0);


}