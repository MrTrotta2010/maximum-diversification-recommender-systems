#!/bin/bash

#$1 é a base
#$2 é o recomendador

#teste=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29)
tabu=(1 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250 260 270 280 290 300 310 320 330 340 350 360 370 380 390 400 410 420 430 440 450 460 470 480 490 500 510 520 530 540 550 560 570 580 590 600 610 620 630 640 650 660 670 680 690 700 710 720 730 740 750 760 770 780 790 800 810 820 830 840 850 860 870 880 890 900 910 920 930 940 950 960 970 980 990 1000)
#teste=(0 1)

for t in "${tabu[@]}" 
do	
	# echo "  Alpha: " $a >> logITS.txt    
	# Cria o diretório de teste
    mkdir ../../Evaluations/ITS_Output/ML-1M/alfa0.5/testesTabu/userKNN$t
   	# Gera um arquivo de teste aleatório
   	#./randomTestITS ../../Evaluations/ITS_Output/ML-1M/alfa0.5/userKNN$t/
   	# Roda o ITS com o arquivo de testes gerado
   	./its ITS ../../Datasets/ML-1M/ ../../Recommendations-Lists/ML-1M/rec_userKNN_conv.txt ../../Evaluations/ITS_Output/ML-1M/alfa0.5/testesTabu/userKNN$t 100 0.5 10 40 $t
done
