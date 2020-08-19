#!/bin/bash

#for i in `seq 1 20 2`;
for (( i=800; i<=10000; i+=80 ));

       do
           echo '#!/bin/bash'  > tmp
	   echo ' ' >> tmp
           echo '#SBATCH -o size-'${i}'-iter-%a-%N.txt' >> tmp
           cat tmp tail.master.sh > slurmjob_size_${i}.bash
	   sbatch --array=0-9 slurmjob_size_${i}.bash $i
           
       done

rm tmp
