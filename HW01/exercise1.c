
/*****************************************************************
//
//  NAME:		Ehsan Kourkchi
//
//  HOMEWORK:		1
//
//  CLASS:		ICS 632
//
//  INSTRUCTOR:		Henri Casanova
//
//  DATE:		September 14, 2015           
//
//  FILE:		exercise1.c   
//
//  DESCRIPTION:	This contains the program for the exersise 1
//
//****************************************************************/
// To compile the program on UHHPC cluster:
// $ icc  exercise1.c -o exercise1.x  -Ofast -D TILE=1 -D N=18000 -D b=10 -mcmodel medium -shared-intel
// N: is the array size 
// b: is the tile size
// TILE: run in the naive mode if set to 0, and in the tiling mode if set to 1
// 
// To compile it on my PC:
// $ gcc exercise1.c -o exercise1.x  -Ofast -D TILE=1 -D N=16000 -D b=10 -mlong-double-64
//
// To run the program:
// $ ./exercise1.x
//
// To use Perf command
// $ perf stat -e L1-dcache-load-misses -e LLC-load-misses ./exercise1.x
//
//****************************************************************/



# include <stdio.h>


#ifndef N
#define N 20
#endif

#ifndef b
#define b 4
#endif

#ifndef TILE
#define TILE 0
#endif

double A[N][N];
double B[N][N];






int main(int argc, char *argv[])
{
    int i, j, Ti, Tj;
    int N_tile = N/b;
    
    printf("\nN = %d  \nb = %d \nTILE = %d \n", N, b, TILE);
    
    
    // Initialiazing for test
    /* for (i=0; i<N; i++)
    {
      for (j=0; j<N; j++)
      {
	A[i][j] = i+j;
	B[i][j] = (i+1)*(j+1);
      }
    }  */
    
    
// To run in the naive mode  
#if TILE == 0

    
    printf("TILE = NO \n");
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	A[i][j]+= B[j][i];
    

// To run in the tiling mode.
#elif TILE == 1

    

    printf("TILE = YES \n");
    for (Ti=0; Ti<N_tile; Ti++)
      for (Tj=0; Tj<N_tile; Tj++)
	for (i=Ti*b; i<(Ti+1)*b; i++)
	  for (j=Tj*b; j<(Tj+1)*b; j++)
	     A[i][j]+= B[j][i];


// If N is not divisible by b, then the remaining 
// column and row, as well as the smallest square tile
// would be considerred in this section

    if (N - N_tile*b !=0)
    {
      Ti = N_tile;
        for (Tj=0; Tj<N_tile; Tj++)
	  for (i=Ti*b; i<N; i++)
	    for (j=Tj*b; j<(Tj+1)*b; j++)
	       A[i][j]+= B[j][i];

      Tj = N_tile;
        for (Ti=0; Ti<N_tile; Ti++)
	  for (i=Ti*b; i<(Ti+1)*b; i++)
	    for (j=Tj*b; j<N; j++)
	       A[i][j]+= B[j][i];	
	    

// The last piece of the array which is an small square array of size w*w, 
// where w = N - N_tile*b
      Tj = N_tile;
      for (i=Ti*b; i<N; i++)
	for (j=Tj*b; j<N; j++)
	   A[i][j]+= B[j][i];
    }
    
    
 
    
#endif
    



  
}  // END
