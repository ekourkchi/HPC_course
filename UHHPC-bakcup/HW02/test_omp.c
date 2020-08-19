
# include <stdio.h>
# include <omp.h>

// compile:
// gcc test_omp.c -o test_omp.x -fopenmp

int main(int argc, char *argv[])
{
    int iam=0, np=1;
    


   #pragma omp parallel
  {
      printf("Hello World. \n"); 
  }
   
   
  #pragma omp parallel private(iam,np)
  {
    np = omp_get_num_threads();  // Total number of threads
    iam = omp_get_thread_num();  // Current thread number
    printf("Hello from thread %d out of %d threads\n", iam, np);
  }
 
  
  
  
return(0);


}