#!/bin/bash

# $1 is the Open-MP parallel mode 
export mode=$1

  for i in `seq 1 20`;
    do
      sbatch myslurm.slurm $mode $i
  done 




