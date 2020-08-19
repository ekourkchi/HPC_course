
/*****************************************************************
//
//  NAME:		Ehsan Kourkchi
//
//  HOMEWORK:		2
//
//  CLASS:		ICS 632
//
//  INSTRUCTOR:		Henri Casanova
//
//  DATE:		September 30, 2015           
//
//  FILE:		exercise2_fast.c
//
//  DESCRIPTION:	This contains the program for the exersise 1
//
//****************************************************************/
// To compile the program on UHHPC cluster:
// $ icc exercise2_fast.c -o exercise2_fast.x  -Ofast -fopenmp -mcmodel medium -shared-intel
//
// 
// To compile it on my PC:
// $ gcc exercise2_fast.c -o exercise2_fast.x  -Ofast  -mlong-double-64 -fopenmp
//
// To run the program:
// $ ./exercise2_fast.x
//
// To use Perf command
// $ perf stat -e L1-dcache-load-misses -e LLC-load-misses ./exercise2.x
//
//****************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
# include <omp.h>

#ifndef TILESIZE
#define TILESIZE 1500
#endif

#define N 12000

int A[N+2][N+2], B[N+2][N+2];

int main(int argc, char **argv) {

  int num_threads;
  int num_iterations;

  int iter;
  int i,j, n, p, q, n_tiles, ii, jj;

  if (argc != 3) {
	  fprintf(stderr,"Usage: %s <num threads> <num iterations>\n", argv[0]);
	  exit(1);
  }

  if (sscanf(argv[1],"%d",&num_threads) != 1) {
	  fprintf(stderr,"Invalid number of threads\n");
	  exit(1);
  }

  if (sscanf(argv[2],"%d",&num_iterations) != 1) {
	  fprintf(stderr,"Invalid number of iterations\n");
	  exit(1);
  }
  
  // Fill in the array
  for (i=0; i < N+2; i++) {
    for (j=0; j < N+2; j++) {
      A[i][j] = B[i][j] = i+j;
    }
  }
  
  
  
  
  

  // Loop for num_iterations iterations
  for (iter = 0; iter < num_iterations; iter++) {
    
    n_tiles = N / TILESIZE;
    
    for (p=0; p < n_tiles; p++) {
      for (q=0; q < n_tiles; q++) {
    
	  for (n=1; n < TILESIZE+1; n++) {
	    #pragma omp parallel for shared(A) \
	      private(j)
	    for (i=1; i < n+1; i++) {
	      j = n - (i-1);
	      ii = i + p * TILESIZE;
	      jj = j + q * TILESIZE;
	      A[ii][jj] = (3*A[ii-1][jj] + A[ii+1][jj] + 3*A[ii][jj-1] + A[ii][jj+1])/4; }}
	      
	  for (n=TILESIZE+1; n < 2*TILESIZE; n++) {
	    #pragma omp parallel for shared(A) \
	      private(j)
	    for (i=n-TILESIZE+1; i < TILESIZE+1; i++) {
	      j = n - (i-1);
	      ii = i + p * TILESIZE;
	      jj = j + q * TILESIZE;
	      A[ii][jj] = (3*A[ii-1][jj] + A[ii+1][jj] + 3*A[ii][jj-1] + A[ii][jj+1])/4; }}
	
      }}

    }
  

  
  
  
  
  
  
  // Compute and print the sum of elements for correctness checking
//   int sum =0 ;
//   for (i=1; i < N; i++) {
//     for (j=1; j < N; j++) {
//       sum += A[i][j];
//     }
//   }
//   fprintf(stderr,"sum = %d\n",sum);

  exit(0);
}
