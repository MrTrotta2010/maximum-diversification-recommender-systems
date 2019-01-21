#!/bin/bash

#$1 é a base
#$2 é o recomendador

alpha=(0.000000 0.250000 0.500000 0.750000 1.000000)

for a in "${alpha[@]}" 
do	
	echo "  Alpha: " $a >> logMDRS.txt
    ./runMDRS.sh $a $1 $2

done

