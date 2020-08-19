#!/bin/bash  
#SBATCH -n 1 # Number of cores requested
#SBATCH -N 1 # Ensure that all cores are on one machine
#SBATCH -t 1 # Runtime in minutes
#SBATCH -p community.q# Partition to submit to the standard compute node partition in this example
#SBATCH -o example.out # Standard out goes to this file
#SBATCH -e example.err # Standard err goes to this file 
#SBATCH --mail-type ALL
#SBATCH --mail-user @hawaii.edu
Rscript hello.R
