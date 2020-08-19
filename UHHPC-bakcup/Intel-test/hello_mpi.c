#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
  int mype, npes;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &mype);
  MPI_Comm_size(MPI_COMM_WORLD, &npes);

  printf("Hello world from process %d of %d!\n", mype, npes);

  return MPI_Finalize();
}
