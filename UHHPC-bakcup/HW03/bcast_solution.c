
/*****************************************************************
//
//  NAME:		Ehsan Kourkchi
//
//  HOMEWORK:		3
//
//  CLASS:		ICS 632
//
//  INSTRUCTOR:		Henri Casanova
//
//  DATE:		October 20, 2015           
//
//  FILE:		bcast_skeleton.c  bcast_solution.c
//
//  DESCRIPTION:	This contains the program for the exersise 3
//
//****************************************************************/
/* To compi: > make all 

 To run this code: 
 > smpirun --cfg=smpi/bcast:mpich --cfg=smpi/running_power:1Gf -np <num processes> -platform <XML platform file> -hostfile <host file> ./bcast_skeleton [-c <chunk size>] [-s <message string>]

 Example
 smpirun --cfg=smpi/bcast:mpich --cfg=smpi/running_power:1Gf -np 5 -platform ring_5.xml -hostfile hostfile_5 ./bcast_skeleton -c 10
 
 To make hostfiles and platform files, use the python code:
 Example: > python generate_xml_and_host_files.py 5
 where 5 is the number of hosts.
 
 */

#ifndef MODE
#define MODE 0
#endif


//****************************************************************/
// Default Broadcast
// bcast_default
#if MODE == 0
   MPI_Bcast(buffer, NUM_BYTES, MPI_CHAR, 0, MPI_COMM_WORLD);
#endif
   

//****************************************************************/
// Naive broadcast
// print statement are made for pedagogical sake
// bcast_naive
#if MODE == 1
   
   MPI_Status status;
   MPI_Request request = MPI_REQUEST_NULL;

   if (rank == 0) {
     for (j=1; j < num_procs; j++) {
//          printf("time of send: %.3lf ... to process #%d\n", MPI_Wtime() - start_time, j);
         MPI_Send(buffer, NUM_BYTES, MPI_CHAR, j, 0, MPI_COMM_WORLD);
// 	 printf("time of receive: %.3lf ... process #%d\n", MPI_Wtime() - start_time, j);
     }
      
  } // end process for the root
  
  else { // other processes
     MPI_Recv(buffer, NUM_BYTES, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
     
  }

     
#endif

     
//****************************************************************/
// Ring broadcast on a ring
// print statement are made for pedagogical sake
// bcast_ring
#if MODE == 2
   
   MPI_Status status;
   MPI_Request request = MPI_REQUEST_NULL;
   

   if (rank == 0) {
//         printf("time of send: %.3lf ... to process #%d\n", MPI_Wtime() - start_time, 1);
        MPI_Send(buffer, NUM_BYTES, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
// 	printf("time of receive: %.3lf ... process #%d\n", MPI_Wtime() - start_time, 1);
	MPI_Recv(buffer, NUM_BYTES, MPI_CHAR, (num_procs-1), 1, MPI_COMM_WORLD, &status);
	
	
   }
   
   else {
   MPI_Recv(buffer, NUM_BYTES, MPI_CHAR, (rank-1) % num_procs, 1, MPI_COMM_WORLD, &status);
//     printf("time of send: %.3lf ... to process #%d\n", MPI_Wtime() - start_time, (rank+1) % num_procs);
   MPI_Send(buffer, NUM_BYTES, MPI_CHAR, (rank+1) % num_procs, 1, MPI_COMM_WORLD);
//    printf("time of receive: %.3lf ... process #%d\n", MPI_Wtime() - start_time, (rank+1) % num_procs);
    
   }
   
   
          
#endif   


//****************************************************************/
// Pieplined Ring Broadcast on a Ring
// bcast_ring_pipelined
#if MODE == 3

   MPI_Status status;
   MPI_Request request = MPI_REQUEST_NULL;
   int n_chunk = NUM_BYTES / chunk_size;
   int r_chunk = NUM_BYTES % chunk_size;
   
   if (rank == 0) {  // root 
      
      // broadcast as many as the number of nodes
      for (i=0; i<num_procs-1 && i<n_chunk; i++) 
	  MPI_Send(buffer+i*chunk_size, chunk_size, MPI_CHAR, 1, i, MPI_COMM_WORLD);
      
      // then perform a receive and a send in row
      for (j=0; j<n_chunk; j++)  { 
	  
	  MPI_Recv(buffer+j*chunk_size, chunk_size, MPI_CHAR, (num_procs-1), j, MPI_COMM_WORLD, &status); 
	  if (i<n_chunk) {
	      MPI_Send(buffer+i*chunk_size, chunk_size, MPI_CHAR, 1, i, MPI_COMM_WORLD);
	      i++; 
	  }
	  else if (i==n_chunk && r_chunk!=0) {
	      MPI_Send(buffer+i*chunk_size, r_chunk, MPI_CHAR, 1, i, MPI_COMM_WORLD);
	      i++; 
	  }

      }
      
      if (r_chunk!=0)    // in the case chunk_size does not count NUM_BYTES
	MPI_Recv(buffer+j*chunk_size, chunk_size, MPI_CHAR, (num_procs-1), j, MPI_COMM_WORLD, &status);
      

   
   } else {  // not root
      
      // first receive a chunk and then send it
      for (i=0; i<n_chunk; i++) {
        MPI_Recv(buffer+i*chunk_size, chunk_size, MPI_CHAR, (rank-1) % num_procs, i, MPI_COMM_WORLD, &status);
        MPI_Send(buffer+i*chunk_size, chunk_size, MPI_CHAR, (rank+1) % num_procs, i, MPI_COMM_WORLD); 
      }
      
      if (r_chunk!=0) {
          MPI_Recv(buffer+i*chunk_size, r_chunk, MPI_CHAR, (rank-1) % num_procs, i, MPI_COMM_WORLD, &status);
          MPI_Send(buffer+i*chunk_size, r_chunk, MPI_CHAR, (rank+1) % num_procs, i, MPI_COMM_WORLD); 
      }

  }  // end-else
  
   


#endif

  
//****************************************************************/
// Pipeline Ring Broadcast with Isend on a ring
// This routine is exactly the same as the previous one
// It used MPI_Isend instead of MPI_Send
// bcast_ring_pipelined_isend
#if MODE == 4
   
   MPI_Status status;
   MPI_Request request = MPI_REQUEST_NULL;
   int n_chunk = NUM_BYTES / chunk_size;
   int r_chunk = NUM_BYTES % chunk_size;
   
   if (rank == 0) { // root
   for (i=0; i<num_procs-1 && i<n_chunk; i++) 
      MPI_Isend(buffer+i*chunk_size, chunk_size, MPI_CHAR, 1, i, MPI_COMM_WORLD, &request);
      MPI_Wait( &request, MPI_STATUS_IGNORE );    // wait until the last send is done
   
   for (j=0; j<n_chunk; j++)  { 
       MPI_Recv(buffer+j*chunk_size, chunk_size, MPI_CHAR, (num_procs-1), j, MPI_COMM_WORLD, &status); 
       MPI_Wait( &request, MPI_STATUS_IGNORE );    // wait until the last send is done
       if (i<n_chunk) {
          MPI_Isend(buffer+i*chunk_size, chunk_size, MPI_CHAR, 1, i, MPI_COMM_WORLD, &request);
          i++; }
       else if (i==n_chunk && r_chunk!=0) {
          MPI_Isend(buffer+i*chunk_size, r_chunk, MPI_CHAR, 1, i, MPI_COMM_WORLD, &request);
          i++; }

   }  // end-for
   
   if (r_chunk!=0)
     MPI_Recv(buffer+j*chunk_size, chunk_size, MPI_CHAR, (num_procs-1), j, MPI_COMM_WORLD, &status);

   
   } else {  // not root
      
      
     for (i=0; i<n_chunk; i++) {
       
        MPI_Recv(buffer+i*chunk_size, chunk_size, MPI_CHAR, (rank-1) % num_procs, i, MPI_COMM_WORLD, &status);
	MPI_Wait( &request, MPI_STATUS_IGNORE );    // wait until the last send is done
        MPI_Isend(buffer+i*chunk_size, chunk_size, MPI_CHAR, (rank+1) % num_procs, i, MPI_COMM_WORLD, &request); 
	
      } // end-for
      
      if (r_chunk!=0) {
	
          MPI_Recv(buffer+i*chunk_size, r_chunk, MPI_CHAR, (rank-1) % num_procs, i, MPI_COMM_WORLD, &status);
	  MPI_Wait( &request, MPI_STATUS_IGNORE );    // wait until the last send is done
          MPI_Isend(buffer+i*chunk_size, r_chunk, MPI_CHAR, (rank+1) % num_procs, i, MPI_COMM_WORLD, &request); 
      }

  }  // end-else
  
   


#endif


//****************************************************************/
// Binary tree broadcast on a tree 
// bcast_bintree_pipelined_isend
#if MODE == 5


  
  MPI_Status status;
  MPI_Request request1 = MPI_REQUEST_NULL;
  MPI_Request request2 = MPI_REQUEST_NULL;
  int n_chunk = NUM_BYTES / chunk_size;
  int r_chunk = NUM_BYTES % chunk_size;
  
  
  // root, just sends chunks to its children
  if (rank == 0) { // root
   
      
      for (i=0; i<n_chunk; i++) {
	if (1<num_procs) {
	    MPI_Isend(buffer+i*chunk_size, chunk_size, MPI_CHAR, 1, i, MPI_COMM_WORLD, &request1);
	    if (2<num_procs) {
	      if (i>0)  // make sure that the previous chunk has been received by the right child
		MPI_Wait( &request2, MPI_STATUS_IGNORE );
	      MPI_Isend(buffer+i*chunk_size, chunk_size, MPI_CHAR, 2, i, MPI_COMM_WORLD, &request2); }
	    MPI_Wait( &request1, MPI_STATUS_IGNORE );   // make sure that the previous chunk has been received by the left child
	}}
	  
 
      if (r_chunk!=0) {
	
	if (1<num_procs) {
	    MPI_Isend(buffer+i*chunk_size, r_chunk, MPI_CHAR, 1, i, MPI_COMM_WORLD, &request1);
	    if (2<num_procs) {
	        if (i>0) 
		  MPI_Wait( &request2, MPI_STATUS_IGNORE );
	        MPI_Isend(buffer+i*chunk_size, r_chunk, MPI_CHAR, 2, i, MPI_COMM_WORLD, &request2); 
	    }
	    MPI_Wait( &request1, MPI_STATUS_IGNORE ); 
	}
      }
   
  
   } else {  // not root --> first receive a chunk from your parent and then possibly send it to your children
     
     // the ranks of left and right children
     int left = 2*rank +1;
     int right = 2*rank +2;
     
     for (i=0; i<n_chunk; i++) {
       // receiving from the parent node
        MPI_Recv(buffer+i*chunk_size, chunk_size, MPI_CHAR, (rank-1)/2, i, MPI_COMM_WORLD, &status);
	if (left<num_procs) {
	    MPI_Isend(buffer+i*chunk_size, chunk_size, MPI_CHAR, left, i, MPI_COMM_WORLD, &request1);
	    if (right<num_procs) {
	      if (i>0) 
		MPI_Wait( &request2, MPI_STATUS_IGNORE );
	      MPI_Isend(buffer+i*chunk_size, chunk_size, MPI_CHAR, right, i, MPI_COMM_WORLD, &request2); 
            }
	    
	    MPI_Wait( &request1, &status ); 
	}
     }  // end-for
     
      // if there is any piece of data remained at the end
      if (r_chunk!=0) {
	MPI_Recv(buffer+i*chunk_size, r_chunk, MPI_CHAR, (rank-1)/2, i, MPI_COMM_WORLD, &status);
	if (left<num_procs) {
	    MPI_Isend(buffer+i*chunk_size, r_chunk, MPI_CHAR, left, i, MPI_COMM_WORLD, &request1);
	    if (right<num_procs) {
	      if (i>0) 
		MPI_Wait( &request2, MPI_STATUS_IGNORE );
	      MPI_Isend(buffer+i*chunk_size, r_chunk, MPI_CHAR, right, i, MPI_COMM_WORLD, &request2); }
	    
	    MPI_Wait( &request1, &status ); 
	}

      }     //end of outer if
     

   }
 

#endif

//****************************************************************/

