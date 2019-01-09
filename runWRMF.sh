#!/bin/bash

#files=("CIAO/CiaoDVD" "ML-10M" "ML-20M" "Amazon/VideoGames/v=5" "Amazon/VideoGames/v=10" "Amazon/Clothes/v=5" "Amazon/Clothes/v=10" "Yahoo/Movies" "ML-Latest/later2012")
files=("CIAO/CiaoDVD")

touch log.txt
sudo chmod 777 log.txt
date "+%H:%M:%S   %d/%m/%y" > log.txt
echo "" >> log.txt

for f in "${files[@]}" 
do	

	echo "----------------------------------" >> log.txt
	echo "Dataset " $f >> log.txt
	echo "----------------------------------" >> log.txt

	echo "WRMF" >> log.txt
	echo "WRMF"
	item_recommendation --training-file=Datasets/CIAO/CiaoDVD/trainSet.csv	 --test-file=Datasets/CIAO/CiaoDVD/testSet.csv --recommender=WRMF --prediction-file=Recommendations-Lists/CIAO/rec_WRMF.txt --predict-items-number=100 2>>log.txt >> log.txt

	echo "" >> log.txt
	echo "----------------------------------------------------------------------------------" >> log.txt
	echo "" >> log.txt

done

