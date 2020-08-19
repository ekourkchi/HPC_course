
/*****************************************************************
//
//  NAME:		Ehsan Kourkchi
//
//  HOMEWORK:		4
//
//  CLASS:		ICS 632
//
//  INSTRUCTOR:		Henri Casanova
//
//  DATE:		November 7, 2015           
//
//  FILE:		hw04.skeleton.c
//
//  DESCRIPTION:	
//****************************************************************/
/* To compi: >
 * 
 To run this code on my desktop computer: 
 > smpirun --cfg=smpi/bcast:mpich --cfg=smpi/running_power:0.047 -np 4 -platform cluster_1600.xml -hostfile hostfile_1600.bin ./matmul_init
 > smpirun --cfg=smpi/bcast:mpich --cfg=smpi/running_power:0.047 -np 16 -platform cluster_1600.xml -hostfile hostfile_1600.bin ./matmul_outerproduct_v1 -n 1600
 
 Compile:
 >  make all
 - smpicc -O4  hw04.skeleton.c -D MODE=0 -lm -o matmul_init
 - smpicc -O4  hw04.skeleton.c -D MODE=1 -lm -o matmul_outerproduct_v1 -fopenmp
 - smpicc -O4  hw04.skeleton.c -D MODE=1 -lm -o matmul_outerproduct_v1_omp -fopenmp -D OMP=1
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <string.h>
#include <math.h>

#ifndef OMP
#define OMP 0
#endif

#if OMP==1
#include <omp.h>
#endif




#ifndef Size
#define Size 4
#endif

#ifndef FLOP
#define FLOP 1
#endif

// Function declaration
int set(double *buffer, double *original, int size);
int MatrixMultiplyAdd(double *C, double *buffer_A, double *buffer_B, int n);

///////////////////////////////////////////////////////
//// program_abort() and print_usage() functions //////
///////////////////////////////////////////////////////

static void program_abort(char *exec_name, char *message);
static void print_usage();


// Abort, printing the usage information only if the
// first argument is non-NULL (and set to argv[0]), and
// printing the second argument regardless.
static void program_abort(char *exec_name, char *message) {
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  if (my_rank == 0) {
    if (message) {
      fprintf(stderr,"%s",message);
    }
    if (exec_name) {
      print_usage(exec_name);
    }
  }
  MPI_Abort(MPI_COMM_WORLD, 1);
  exit(1);
}

// Print the Usage information
static void print_usage(char *exec_name) {
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  if (my_rank == 0) {
    fprintf(stderr,"\n Usage: mpirun --cfg=smpi/bcast:mpich --cfg=smpi/running_power:<VALUE> -np <num processes>\n");
    fprintf(stderr,"              -platform <XML platform file> -hostfile <host file> %s [-n <matrix dimension>]\n",exec_name);
    fprintf(stderr,"\n MPIRUN arguments:\n");
    fprintf(stderr,"\t<num processes>: number of MPI processes\n");
    fprintf(stderr,"\t<XML platform file>: a simgrid platform description file\n");
    fprintf(stderr,"\t<host file>: MPI host file with host names from the XML platform file\n");
    fprintf(stderr,"\t<VALUE>: run \"generate_xml_and_host_files.py\" on your machine to get this value.\n");
    fprintf(stderr,"\n PROGRAM arguments:\n");
    fprintf(stderr,"\t[-n <matrix dimension>]\n");
    fprintf(stderr,"\t[-f <a floating point number> i.e. The computation power, higher is less power, and longer runing time]\n");
    fprintf(stderr,"\t[--verbose]: verbose \n");
    fprintf(stderr,"\t[-h, --help]: To see this help \n");
    fprintf(stderr,"\n NOTE:\n");
    fprintf(stderr,"\t- Number of processes must be perfect square.\n");
    fprintf(stderr,"\t- The matrix dimension must be divisible by the SQRT of # of processes. \n");
    fprintf(stderr,"\n");
  }
}

///////////////////////////
////// Main function //////
///////////////////////////



int main(int argc, char *argv[])
{
  
  int i,j, k;
  int verbose = 0;

  // Parse command-line arguments (not using getopt because not thread-safe
  // and annoying anyway). The code below ignores extraneous command-line
  // arguments, which is lame, but we're not in the business of developing
  // a cool thread-safe command-line argument parser.

  MPI_Init(&argc, &argv);
  
  
  
  // Matrix dimension optional argument
  int N = Size;
  for (i=1; i < argc; i++) {
    if (!strcmp(argv[i],"-n")) {
      if ((i+1 >= argc) || (sscanf(argv[i+1],"%d",&N) != 1)) {
        program_abort(argv[0]," Invalid <matrix dimension> argument\n");
      }
    }
  }

  double FLOP_CALIBRATION_FACTOR = FLOP;
  for (i=1; i < argc; i++) {
    if (!strcmp(argv[i],"-f")) {
      if ((i+1 >= argc) || (sscanf(argv[i+1],"%lf",&FLOP_CALIBRATION_FACTOR) != 1)) {
        program_abort(argv[0]," Invalid <flop> argument\n");
      }
    }
  }  
  
  
  for (i=1; i < argc; i++) {
    if (!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")) {
       program_abort(argv[0],"\n");
      }
  }
  
  for (i=1; i < argc; i++) {
    if (!strcmp(argv[i],"--verbose")) {
       verbose = 1;
      }
  }  
  
  

  
  // Determine rank and number of processes
  int num_procs;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  
   
  // p is # of processors
  // p1 is sqrt(p)
  float p1 = sqrt(num_procs);
  if (p1 != floor(p1))
    program_abort(argv[0],"\n Invalid number of processors.\n");
  
  float n1 = N/p1;
  if (n1 != floor(n1))
    program_abort(argv[0],"\n Matrix dimension is not divisible by sqrt(p),\n where p is the number of processors.\n");
  
  if (rank ==0) {
    printf("\n Matrix size: %dx%d\n", N, N);
    printf(" # of processors: %d\n\n", num_procs);
  }
  

  #include "hw04.library.c"
  
  MPI_Finalize();
  
  return 0;
}



/////////////////////////////
////// OTHER functions //////
/////////////////////////////


// Copying the content of "original" into "buffer"
// size is the length of the arrays, i.e. original and buffer (must have the same size)
int set(double *buffer, double *original, int size)
{
  
  int i;
  for(i = 0; i<size; i++)
    buffer[i] = original[i];
   
  return 0;
}



// The serial Matrix Multiplication
// N is the matrix dimension
// C = C + A*B
int MatrixMultiplyAdd(double *C, double *A, double *B, int n)
{
  
  int k, i, j;
  

#if OMP == 1
  
     #pragma omp parallel for shared(A,B,C) \
 	    private(i, k, j)
     for(i=0; i<n; i++) {
       for(k=0; k<n; k++) {
 	for(j=0; j<n; j++) {
	 C[n*i+j] += A[n*i+k] * B[n*k+j]; 
 	}}}
#else

    for(k = 0; k<n; k++) {
      for(i = 0; i<n; i++) {
        for(j = 0; j<n; j++) {
	  C[n*i+j] += A[n*i+k] * B[n*k+j];
      }}}
   
  
#endif

return 0;
  
}