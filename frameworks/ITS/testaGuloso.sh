#!/bin/bash

#$1 é a base
#$2 é o recomendador

alfas=(0 0.25 0.5 0.75 1)

for a in "${alfas[@]}" 
do	
	echo "Alfa: " $a
	# Cria o diretório de teste
    #mkdir ../../Evaluations/Guloso_Output/ML-1M/testes/userKNN/alfa$a
    mkdir ../../Evaluations/Guloso_Output/CIAO/testes/userKNN/alfa$a
   	# Roda o Guloso
   	#./its Guloso ../../Datasets/ML-1M/ ../../Recommendations-Lists/ML-1M/rec_userKNN_conv.txt ../../Evaluations/Guloso_Output/ML-1M/testes/userKNN/alfa$a 100 $a 10
   	./its Guloso ../../Datasets/CIAO/ ../../Recommendations-Lists/CIAO/rec_userKNN_conv.txt ../../Evaluations/Guloso_Output/CIAO/testes/userKNN/alfa$a 100 $a 10
done
