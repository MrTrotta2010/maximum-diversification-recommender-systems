#!/bin/bash

#$1 é a base
#$2 é o recomendador

#teste=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29)
vizinhos=(1 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100)
#teste=(0 1)

for v in "${vizinhos[@]}" 
do	
	# echo "  Alpha: " $a >> logITS.txt    
	# Cria o diretório de teste
    mkdir ../../Evaluations/ITS_Output/CIAO/alfa0.5/userKNN$v
   	# Gera um arquivo de teste aleatório
   	#./randomTestITS ../../Evaluations/ITS_Output/ML-1M/alfa0.5/userKNN$t/
   	# Roda o ITS com o arquivo de testes gerado
   	./its ITS ../../Datasets/CIAO/ ../../Recommendations-Lists/CIAO/rec_userKNN_conv.txt ../../Evaluations/ITS_Output/CIAO/alfa0.5/userKNN$v 100 0.5 10 $v 20
done
