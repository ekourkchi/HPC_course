# /*****************************************************************
# //
# //  NAME:		Ehsan Kourkchi
# //
# //  HOMEWORK:		4
# //
# //  CLASS:		ICS 632
# //
# //  INSTRUCTOR:	Henri Casanova
# //
# //  FILE:		Makefile        
# //
# //****************************************************************/


all: matmul_init matmul_outerproduct_v1 matmul_outerproduct_v1_omp


matmul_outerproduct_v1: hw04.skeleton.c  hw04.library.c
	mpicc -O4  hw04.skeleton.c -D MODE=1 -lm -o matmul_outerproduct_v1


matmul_init: hw04.skeleton.c hw04.library.c
	mpicc -O4  hw04.skeleton.c -D MODE=0 -lm -o matmul_init


matmul_outerproduct_v1_omp: hw04.skeleton.c hw04.library.c
	mpicc -O4  hw04.skeleton.c -D MODE=1 -lm -o matmul_outerproduct_v1_omp -fopenmp -D OMP=1

.PHONY: clean

clean:
	rm -f matmul_init matmul_outerproduct_v1 matmul_outerproduct_v1_omp
