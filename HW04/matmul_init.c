
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
//  FILE:		matmul_init.c
//
//  DESCRIPTION:	
//****************************************************************/
/* To compi: >
 * 
 To run this code on my desktop computer: 
 > smpirun --cfg=smpi/bcast:mpich --cfg=smpi/running_power:45Mf -np 4 -platform cluster_crossbar_4.xml -hostfile hostfile_4 ./matmul_init

 Compile:
 >  smpicc  -O4 matmul_init.c -o matmul_init  -D Size=4
 
 To make hostfiles and platform files, use the python code:
 Example: > python generate_xml_and_host_files.py 5
 where 5 is the number of hosts.
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <string.h>
#include <math.h>


#ifndef Size
#define Size 4
#endif




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
  
  int i,j;

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

  
  for (i=1; i < argc; i++) {
    if (!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")) {
       program_abort(argv[0],"\n");
      }
  }

  // Determine rank and number of processes
  int num_procs;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  // Allocate buffer
  int checksum;
  char *buffer;
  
  double *A,*B,*C;
//   if ((buffer = malloc(sizeof(char) * NUM_BYTES)) == NULL) {
//     program_abort(argv[0],"Out of memory!");
//   }
  
  
  // p is # of processors
  // p1 is sqrt(p)
  float p1 = sqrt(num_procs);
  if (p1 != floor(p1))
    program_abort(argv[0],"\n Invalid number of processors.\n");
  
  int n = N/p1;
  if (n != floor(n))
    program_abort(argv[0],"\n Matrix dimension is not divisible by sqrt(p),\n where p is the number of processors.\n");
  
  if (rank ==0) {
    printf("\n Matrix size: %dx%d\n", N, N);
    printf(" # of processors: %d\n\n", num_procs);
  }
  
  int p2 = p1;
  
  A = malloc(n*n*sizeof(double));
  B = malloc(n*n*sizeof(double));
  C = malloc(n*n*sizeof(double));
  
  
  int Pi = floor(rank/p2);
  int Pj = rank % p2;
  int dummy=0;
  
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
        A[i*n+j] = i + n*Pi;
        B[i*n+j] = (i+n*Pi)+(j+n*Pj);
        C[i*n+j] = 0;
  }}
  
  
  MPI_Status status;
  MPI_Request request = MPI_REQUEST_NULL;
   
  if (rank == 0) {

    printf("Block of A on rank %d at coordinates (%d,%d)\n", rank, Pi, Pj);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%lf ", A[i*n+j]); }
      printf("\n");
    }
    
    MPI_Ssend(&dummy, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    
  } else {
    
    MPI_Recv(&dummy, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
    printf("Block of A on rank %d at coordinates (%d,%d)\n", rank, Pi, Pj);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%lf ", A[i*n+j]); }
      printf("\n");
    }
  
    MPI_Ssend(&dummy, 1, MPI_INT, (rank+1)%num_procs, 0, MPI_COMM_WORLD);
  
  }
  
  if (rank == 0)
    MPI_Recv(&dummy, 1, MPI_INT, num_procs-1, 0, MPI_COMM_WORLD, &status);
  
   MPI_Barrier(MPI_COMM_WORLD);
  
  if (rank == 0) {

    printf("Block of B on rank %d at coordinates (%d,%d)\n", rank, Pi, Pj);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%lf ", B[i*n+j]); }
      printf("\n");
    }
    
    MPI_Ssend(&dummy, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    
  } else {
    
    MPI_Recv(&dummy, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
    printf("Block of B on rank %d at coordinates (%d,%d)\n", rank, Pi, Pj);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%lf ", B[i*n+j]); }
      printf("\n");
    }
  
    MPI_Ssend(&dummy, 1, MPI_INT, (rank+1)%num_procs, 1, MPI_COMM_WORLD);
  
  }
  
  if (rank == 0)
    MPI_Recv(&dummy, 1, MPI_INT, num_procs-1, 1, MPI_COMM_WORLD, &status); 
  
  
  
  return 0;
}
