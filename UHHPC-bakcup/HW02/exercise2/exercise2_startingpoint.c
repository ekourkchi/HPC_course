
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
//  FILE:		exercise2_startingpoint.c
//
//  DESCRIPTION:	This contains the program for the exersise 1
//
//****************************************************************/
// To compile the program on UHHPC cluster:
// $ icc  exercise2_startingpoint.c -o exercise2_startingpoint.x -Ofast  -mcmodel medium -shared-intel
//
//
// N: is the array size 
// MODE: run in serial mode if set to 0, and in parallel mode if it's set to 1..3
// 
// To compile it on my PC:
// $ gcc exercise2_startingpoint.c -o exercise2_startingpoint.x  -Ofast  -mlong-double-64 
//
// To run the program:
// $ ./exercise1.x
//
// To use Perf command
// $ perf stat -e L1-dcache-load-misses -e LLC-load-misses ./exercise1.x
//
//****************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>

#define N 12000

int A[N+2][N+2];

int main(int argc, char **argv) {

  int num_threads;
  int num_iterations;

  int iter;
  int i,j;

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
      A[i][j] = i+j;
    }
  }

  // Loop for num_iterations iterations
  for (iter = 0; iter < num_iterations; iter++) {
    for (i = 1; i < N+1; i++) {
      for (j = 1; j < N+1; j++) {
        A[i][j] = (3*A[i-1][j] + A[i+1][j] + 3*A[i][j-1] + A[i][j+1])/4;
      }
    }
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
