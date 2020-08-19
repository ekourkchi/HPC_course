# /*****************************************************************
# //
# //  NAME:		Ehsan Kourkchi
# //
# //  HOMEWORK:		3
# //
# //  CLASS:		ICS 632
# //
# //  INSTRUCTOR:	Henri Casanova
# //
# //  DATE:		October 20, 2015           
# //
# //  FILE:		Makefile        
# //
# //  DESCRIPTION:	Makefile for "bcast_skeleton.c"
# //
# //****************************************************************/


all: bcast_default bcast_naive bcast_ring bcast_ring_pipelined bcast_ring_pipelined_isend bcast_bintree_pipelined_isend

bcast_default: bcast_skeleton.c  bcast_solution.c
	smpicc  bcast_skeleton.c -o bcast_default -D MODE=0

bcast_naive: bcast_skeleton.c  bcast_solution.c
	smpicc  bcast_skeleton.c -o bcast_naive -D MODE=1

bcast_ring: bcast_skeleton.c  bcast_solution.c
	smpicc  bcast_skeleton.c -o bcast_ring -D MODE=2

bcast_ring_pipelined: bcast_skeleton.c  bcast_solution.c
	smpicc  bcast_skeleton.c -o bcast_ring_pipelined -D MODE=3

bcast_ring_pipelined_isend: bcast_skeleton.c  bcast_solution.c
	smpicc  bcast_skeleton.c -o bcast_ring_pipelined_isend -D MODE=4

bcast_bintree_pipelined_isend: bcast_skeleton.c  bcast_solution.c
	smpicc  bcast_skeleton.c -o bcast_bintree_pipelined_isend -D MODE=5


.PHONY: clean

clean:
	rm -f bcast_default bcast_naive bcast_ring bcast_ring_pipelined bcast_ring_pipelined_isend bcast_bintree_pipelined_isend

