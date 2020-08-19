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








//>  cc exercise1.c -o exercise1.x  -D N=20 b=4

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
    
    
    
#if TILE == 0

    
    printf("TILE = NO \n");
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	A[i][j]+= B[j][i];
    
      
#elif TILE == 1

    

    printf("TILE = YES \n");
    for (Ti=0; Ti<N_tile; Ti++)
      for (Tj=0; Tj<N_tile; Tj++)
	for (i=Ti*b; i<(Ti+1)*b; i++)
	  for (j=Tj*b; j<(Tj+1)*b; j++)
	     A[i][j]+= B[j][i];


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
	    
	    
      Tj = N_tile;
      for (i=Ti*b; i<N; i++)
	for (j=Tj*b; j<N; j++)
	   A[i][j]+= B[j][i];
    }
    
    
 
    
#endif
    
//     printf("A[0][0] = %f \n", A[0][0]);
//     printf("A[5][4] = %f \n", A[5][4]);
//     printf("A[9][0] = %f \n", A[9][0]);
//     printf("A[0][9] = %f \n", A[0][9]);
//     printf("A[19][9] = %f \n", A[19][9]);


  
}  // END
