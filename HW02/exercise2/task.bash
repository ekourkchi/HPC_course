#!/bin/bash

 export  mode=$1  # OMP parallel mode 
 export  cores=$2 # number of cores 1..20
 touch output.$mode.$cores.txt

 # i starts from 1
  echo 'iteration,  mode, cores, time,  L1-dcache-load-misses,  LLC-load-misses' > output.$mode.$cores.txt
  for i in `seq 1 10`;
     do 
        # Making emty files to deal with the timeout
        touch tmp.$mode.$cores.tmp
        touch out.$mode.$cores.txt

        timeout 10m perf stat -e L1-dcache-load-misses -e LLC-load-misses -o tmp.$mode.$cores.tmp ./exercise2_startingpoint.x 1 17 > out.$mode.$cores.txt
        


        

        
        # L1-dcache-load-misses
        export a=`awk '(NR == 6) {print($1)}' tmp.$mode.$cores.tmp
`
        
        # LLC-load-misses
        export b=`awk '(NR == 7) {print($1)}' tmp.$mode.$cores.tmp`
        
        # elapsed time
        export time=`awk '(NR == 9) {print($1)}' tmp.$mode.$cores.tmp`
        
        # removing comma
        export a=`echo $a | awk '/[0-9]/{gsub(/,/,"")};1'`
        export b=`echo $b | awk '/[0-9]/{gsub(/,/,"")};1'`
        
        echo $i',  '$mode',  '$cores',  '$time',  '$a',  '$b  >> output.$mode.$cores.txt

            

     done 

     rm tmp.$mode.$cores.tmp
     rm out.$mode.$cores.txt
     

