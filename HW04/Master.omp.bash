#!/bin/sh

#for i in `seq 1 20 2`;
for (( i=800; i<=10000; i+=80 ));

       do
           echo '#!/bin/bash'  > tmp
	   echo ' ' >> tmp
           echo '#SBATCH -o size-'${i}'-iter-%a-%N.omp.txt' >> tmp
           cat tmp tail.master.omp.sh > slurmjob_size_${i}.omp.bash
	   sbatch --array=0-9 slurmjob_size_${i}.omp.bash $i
           
       done

rm tmp
