#!/bin/bash

#O primeiro argumento $1 é o alfa
#O segundo argumento $2 é o endereço das entradas, ou seja, o nome do dataset
#O terceiro argumento $3 é o endereço de saída, ou seja, o recomendador utilizado

#files=("ML-1M" "ML-10M" "ML-20M" "Amazon/VideoGames/v=5" "Amazon/VideoGames/v=10" "Amazon/Clothes/v=5" "Amazon/Clothes/v=10" "Yahoo/Movies" "ML-Latest/later2012")

echo "Alpha: " $1

echo "Rodando o MDRS" $2 $3
cd frameworks/MDRS/
#./mdrs $1 $2 $3 #Roda o MDRF
echo "  Rodou MDRS" >> ../../logMDRS.txt

echo "Avaliando as recomendações de base" $2 $3
cd ../EvalRec/
#./eval $2 $3 #Avalia as recomendações base
echo "  Rodou EvalRec" >> ../../logMDRS.txt

echo "Ordenando as avaliações do MDRS"
cd ../../Evaluations/MDRS_Output/
./sortFiles.sh $1 $2 $3
echo "  Ordenou as avaliações do MDRS" >> ../../logMDRS.txt

echo "Ordenando as avaliações das recomendações base"
cd ../Standard/
./sortFiles.sh $2 $3
echo "  Ordenou as avaliações do EvalRec" >> ../../logMDRS.txt

echo "Plotando os gráficos"
cd ../Plots/$2/
gnuplot -e "outputFile='$3/$1/acc.eps'; inputMDRS='../../MDRS_Output/$2/alfa$1/$3/acc.txt'; inputStandard='../../Standard/$2/$3/acc.txt'; titleMDRS='MDRS a=$1'; titleStandard='$3'" plotEvalAcc.gp

gnuplot -e "outputFile='$3/$1/acc_rel.eps'; inputMDRS='../../MDRS_Output/$2/alfa$1/$3/acc_rel.txt'; inputStandard='../../Standard/$2/$3/acc_rel.txt'; titleMDRS='MDRS a=$1'; titleStandard='$3'" plotEvalAccRel.gp 

gnuplot -e "outputFile='$3/$1/div.eps'; inputMDRS='../../MDRS_Output/$2/alfa$1/$3/div.txt'; inputStandard='../../Standard/$2/$3/div.txt'; titleMDRS='MDRS a=$1'; titleStandard='$3'" plotEvalDiv.gp 

gnuplot -e "outputFile='$3/$1/div_rel.eps'; inputMDRS='../../MDRS_Output/$2/alfa$1/$3/div_rel.txt'; inputStandard='../../Standard/$2/$3/div_rel.txt'; titleMDRS='MDRS a=$1'; titleStandard='$3'" plotEvalDivRel.gp  

echo "  Plotou os gráficos" >> ../../../logMDRS.txt

