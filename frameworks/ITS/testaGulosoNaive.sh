#!/bin/bash

#$1 é a base
#$2 é o recomendador

alfas=(0 0.25 0.5 0.75 1)

for a in "${alfas[@]}" 
do	
	echo "Alfa: " $a
	# Cria o diretório de teste
    mkdir ../../Evaluations/GulosoNaive_Output/$1/testes/$2/alfa$a
   	# Roda o Guloso
   	./its GN ../../Datasets/$1/ ../../Recommendations-Lists/$1/rec_$2_conv.txt ../../Evaluations/GulosoNaive_Output/$1/testes/$2/alfa$a 100 $a 10
done
