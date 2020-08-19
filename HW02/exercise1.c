
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
//  DATE:		September 28, 2015           
//
//  FILE:		exercise1.c   
//
//  DESCRIPTION:	This contains the program for the exersise 1
//
//****************************************************************/
// To compile the program on UHHPC cluster:
// $ icc  exercise1.c -o exercise1_0.x  -Ofast -D N=2500 -D MODE=0 -fopenmp -mcmodel medium -shared-intel
//
//
// N: is the array size 
// MODE: run in serial mode if set to 0, and in parallel mode if it's set to 1..3
// 
// To compile it on my PC:
// $ gcc exercise1.c -o exercise1.x  -Ofast -D MODE=0 -D N=2500 -mlong-double-64 -fopenmp
//
// To run the program:
// $ ./exercise1.x
//
// To use Perf command
// $ perf stat -e L1-dcache-load-misses -e LLC-load-misses ./exercise1.x
//
//****************************************************************/



# include <stdio.h>
# include <omp.h>



#ifndef N
#define N 3
#endif

#ifndef MODE
#define MODE 0
#endif


int A[N][N], B[N][N], C[N][N];

int main(int argc, char *argv[])
{
    int i, j, k, sum = 0;
    
    int iam=0, np=1;
    
    
//     printf("\nN = %d  \nMODE = %d \n\n", N, MODE);
    
    for(i=0; i<N; i++) {
      for(j=0; j<N; j++) {
	A[i][j] = B[i][j] = i+j;
	C[i][j] = 0; 
	
      }}
      
    
//     for(i=0; i<N; i++)
//     {
//       for(j=0; j<N; j++)
// 	printf("%d  ", B[i][j]);
//       printf("\n");
//     }
    
//To run in the serial mode 
 #if MODE == 0
 
     for(i=0; i<N; i++)
       for(k=0; k<N; k++)
 	for(j=0; j<N; j++)
 	  C[i][j] += A[i][k]*B[k][j];
     
     
 #endif
 
 
// // No race condition
// // For each fixed i, and fixed k
// // we have different threads with different associated j

 #if MODE == 1
 
     for(i=0; i<N; i++) {
       for(k=0; k<N; k++) {
 
       #pragma omp parallel for shared(A,B,C) \
 	private(j)
 	for(j=0; j<N; j++) {
 	  C[i][j] += A[i][k]*B[k][j]; }
 
	
       }}
 
 #endif
 
 
// // race condition
// // C[i][j] ... if i is fixed, 
// // we have multiple threads with the same j
 #if MODE == 2
 
     for(i=0; i<N; i++) {
       
       #pragma omp parallel for shared(A,B,C) \
 	private(k, j)
       for(k=0; k<N; k++) {
 
 	for(j=0; j<N; j++) {
 	  
           # pragma omp atomic
 	  C[i][j] += A[i][k]*B[k][j]; 
 
 	}}}
 
 #endif
 
 
 #if MODE == 3
 
 
     #pragma omp parallel for shared(A,B,C) \
 	    private(i, k, j)
     for(i=0; i<N; i++) {
   
       for(k=0; k<N; k++) {

 	for(j=0; j<N; j++) {
 	  
 	 // # pragma omp atomic
	  C[i][j] += A[i][k]*B[k][j]; 
 	  
 	}}}
 
 #endif


// Testing the output matrix for small values of N
     printf("\n\n\n");
     for(i=0; i<N; i++)
     {
       for(j=0; j<N; j++)
 	printf("%d  ", C[i][j]);
       printf("\n");
     }

// Testing the output matrix for small values of N
//     printf("\n\n\n");
//     for(i=0; i<9 && i<N; i++)
// 	sum += C[i][i];
//     printf("SUM = %d  \n\n", sum);



return(0);
  
}  // END
