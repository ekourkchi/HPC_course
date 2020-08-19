#!/bin/bash  
#SBATCH -n 1 # Number of cores requested
#SBATCH -N 1 # Ensure that all cores are on one machine
#SBATCH -t 1 # Runtime in minutes
#SBATCH -p lm.q# Partition to submit to the standard compute node partition in this example
#SBATCH -o example2.out # Standard out goes to this file
#SBATCH -e example2.err # Standard err goes to this file  

R CMD BATCH hello2.R
