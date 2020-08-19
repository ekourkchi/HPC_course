//  NAME:		Ehsan Kourkchi
//
//  HOMEWORK:		4
//
//  CLASS:		ICS 632
//
//  INSTRUCTOR:		Henri Casanova
//
//  DATE:		November 9, 2015           
//
//  FILE:		hw04.library.c
//
//  DESCRIPTION:	It's called by hw04.skeleton.c
//****************************************************************/
// MODE = 0: to just print the initialized matrices on every processes
// MODE = 1: Parallel matrix multiplication (outer-production algorithm)


#ifndef MODE
#define MODE 0
#endif




  int p2 = p1;
  int n = N/p2;
  double *A,*B,*C;
  
  #if MODE < 3
  A = (double *)malloc(n*n*sizeof(double));
  B = (double *)malloc(n*n*sizeof(double));
  C = (double *)malloc(n*n*sizeof(double));
  #endif
  
  #if MODE == 3
  A = (double *)SMPI_SHARED_MALLOC(n*n*sizeof(double));
  B = (double *)SMPI_SHARED_MALLOC(n*n*sizeof(double));
  C = (double *)SMPI_SHARED_MALLOC(n*n*sizeof(double));
  #endif
  
  // Pi is the row number of each process in the prcoessing array
  // Pj is the column number of each process in the prcoessing array
  int Pi = floor(rank/p2);
  int Pj = rank % p2;
  int dummy=0;
  
  // Matix initialization
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
        A[i*n+j] = i + n*Pi;
        B[i*n+j] = (i+n*Pi)+(j+n*Pj);
        C[i*n+j] = 0;
  }}

  

// First all processes print matrix A.
// In order to do that by the rank-order and preventing any 
// inference in printing, some messages are passed between
// processes to make sure the prinitng process is done perfectly.
// This might not be an issue i nthe simulation, but working 
// with the real cluster, it's important
#if MODE == 0

  int buffer=0;
    
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
    
    MPI_Ssend(&buffer, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    
  } else {
    
    MPI_Recv(&buffer, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
    printf("Block of A on rank %d at coordinates (%d,%d)\n", rank, Pi, Pj);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%lf ", A[i*n+j]); }
      printf("\n");
    }
  
    MPI_Ssend(&buffer, 1, MPI_INT, (rank+1)%num_procs, 0, MPI_COMM_WORLD);
  
  }
  
  if (rank == 0)
    MPI_Recv(&buffer, 1, MPI_INT, num_procs-1, 0, MPI_COMM_WORLD, &status);
  
  // end of printing Matrix A
  MPI_Barrier(MPI_COMM_WORLD);
  
  // Print Matrix B
  if (rank == 0) {

    printf("Block of B on rank %d at coordinates (%d,%d)\n", rank, Pi, Pj);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%lf ", B[i*n+j]); }
      printf("\n");
    }
    
    MPI_Ssend(&buffer, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    
  } else {
    
    MPI_Recv(&buffer, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
    printf("Block of B on rank %d at coordinates (%d,%d)\n", rank, Pi, Pj);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%lf ", B[i*n+j]); }
      printf("\n");
    }
  
    MPI_Ssend(&buffer, 1, MPI_INT, (rank+1)%num_procs, 1, MPI_COMM_WORLD);
  
  }
  
  if (rank == 0)
    MPI_Recv(&buffer, 1, MPI_INT, num_procs-1, 1, MPI_COMM_WORLD, &status); 

#endif
  
  

#if MODE > 0 
  
  
  double start_time, finish_time, t, t_compute;
  double checksum = 0;
  double *buffer_A, *buffer_B, *temp_A, *temp_B;
   
  #if MODE < 3
  buffer_A = (double *)malloc(n*n*sizeof(double));
  buffer_B = (double *)malloc(n*n*sizeof(double));
  #endif
  
  #if MODE == 3
  buffer_A = (double *)SMPI_SHARED_MALLOC(n*n*sizeof(double));
  buffer_B = (double *)SMPI_SHARED_MALLOC(n*n*sizeof(double));
  #endif
  
  MPI_Comm MPI_ROW_COMM, MPI_COLUMN_COMM;
  
  
  MPI_Comm_split(MPI_COMM_WORLD, Pi, Pj, &MPI_ROW_COMM);
  MPI_Comm_split(MPI_COMM_WORLD, Pj, Pi, &MPI_COLUMN_COMM);
  
  int rank_row, size_row, rank_col, size_col;
  
  MPI_Comm_rank(MPI_ROW_COMM, &rank_row);
  MPI_Comm_size(MPI_ROW_COMM, &size_row);
  
  MPI_Comm_rank(MPI_COLUMN_COMM, &rank_col);
  MPI_Comm_size(MPI_COLUMN_COMM, &size_col);
  
  // printf("rank:%d rank.r:%d size.r:%d rank.c:%d size.c:%d \n",rank,rank_row, size_row, rank_col, size_col);
  
  // Start the timer
  if (rank == 0) {  
    start_time = MPI_Wtime();
  }
  
  k = 0;
  for (k=0; k<p2; k++) {
    
    //set(buffer_A, A, n*n);
    // saving some time by setting the pointer buffer_A = A
    if (Pj == k) {
      temp_A = buffer_A;
      buffer_A = A;
    }
    
    MPI_Bcast(buffer_A, n*n, MPI_DOUBLE, k, MPI_ROW_COMM);
     
    
    //set(buffer_B, B, n*n);
    // saving some time by setting the pointer buffer_B = B
    if (Pi == k) {
      temp_B = buffer_B;
      buffer_B = B;
    }
    
    MPI_Bcast(buffer_B, n*n, MPI_DOUBLE, k, MPI_COLUMN_COMM);
    
    if (rank == 0) t = MPI_Wtime();
    
#if MODE == 1
    MatrixMultiplyAdd(C, buffer_A, buffer_B, n);
#else 
    double flops = pow(n,3) * FLOP_CALIBRATION_FACTOR/1.E10;
    
    SMPI_SAMPLE_FLOPS(flops) {
      //  Matrix Multiplication C = A*B
      //  A, B and C are of size N*N
      //  computations complexity is O(N*3)
    }
#endif
    
    if (rank == 0)  t_compute += MPI_Wtime() - t;
    
    
    if (Pj == k) 
      buffer_A = temp_A;
    
    if (Pi == k) 
      buffer_B = temp_B;
        
    MPI_Barrier(MPI_COMM_WORLD);
  }
  
  if (rank == 0) {  
    finish_time = MPI_Wtime();
  }
  
#if MODE < 2
  if (verbose)
     printf(" ---- Block of C on rank %d at coordinates (%d,%d) ---- \n", rank, Pi, Pj);
  
  
  // Each process calcultates the checksum of its own chunk of C-matrix
  checksum = 0;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      if (verbose) printf("%lf ", C[i*n+j]); 
      checksum = checksum + C[i*n+j];
    }
      if (verbose) printf("\n");
  }
  
  if (verbose) printf("**************\nrank: %d  checksum: %lf \n**************\n",rank, checksum);
#endif
  
  double all_checksum;
  // Checksum is reduced and transferrd from all processes to the root
  MPI_Reduce(&checksum, &all_checksum, 1, MPI_DOUBLE,
               MPI_SUM, 0, MPI_COMM_WORLD);
  
  checksum = all_checksum;
  // Root prints the final results
  // Checking the correctness of calcultated checksum
  // Reporting the running time
  if(rank == 0) {
    
#if MODE < 2
    double sum_C = pow(N,3)*pow(N-1,2)/2.;
    printf("\n checksum:\t\t %lf\n Analytical Sum:\t %lf \n", checksum, sum_C);
    
    if (sum_C == checksum)
      printf(" ** OK ** The Multiplication sounds to be fine. \n\n");
    else
      printf(" Error: Try to find the bug !!! \n\n");
#else
    printf(" ** OK ** The computation part has been simulated ... \n\n");
#endif
    
    fprintf(stdout," Computation + Communication time (sec): %.3lf\n", finish_time - start_time);
    fprintf(stdout," Computation time (sec): %.3lf\n", t_compute);
    fprintf(stdout," Communication time (sec): %.3lf\n\n", (finish_time - start_time) - t_compute);
  }
  
  #if MODE < 3
  free(buffer_A);
  free(buffer_B);
  #endif
  
#endif   
  
#if MODE < 3  
  free(A);
  free(B);
  free(C);
#endif


#if MODE == 3  
  SMPI_SHARED_FREE(buffer_A);
  SMPI_SHARED_FREE(buffer_B);
  SMPI_SHARED_FREE(A);
  SMPI_SHARED_FREE(B);
  SMPI_SHARED_FREE(C);
#endif 

