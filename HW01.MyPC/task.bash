#!/bin/bash

 export  iteration=$1

 # i starts from 1
  echo 'b,  time,  L1-dcache-load-misses,  LLC-load-misses' > output.$iteration.desktop.txt
  for i in `seq 1 300`;
     do 

        #icc  exercise1.c -o exercise1.$iteration.x  -Ofast -D TILE=1 -D N=18000 -D b=$i -mcmodel medium -shared-intel
        gcc exercise1.c -o exercise1.$iteration.x  -Ofast -D TILE=1 -D N=16000 -D b=$i -mlong-double-64


        perf stat -e L1-dcache-load-misses  -o tmp.$iteration.tmp ./exercise1.$iteration.x > out.$iteration.txt
        
        # L1-dcache-load-misses
        export a=`awk '(NR == 6) {print($1)}' tmp.$iteration.tmp
`

        
        # elapsed time
        export time=`awk '(NR == 8) {print($1)}' tmp.$iteration.tmp`
        
        # removing comma
        export a=`echo $a | awk '/[0-9]/{gsub(/,/,"")};1'`
        export b=`echo $b | awk '/[0-9]/{gsub(/,/,"")};1'`
        
        echo $i',  '$time',  '$a  >> output.$iteration.desktop.txt

            

     done 

     rm tmp.$iteration.tmp
     rm out.$iteration.txt
     

