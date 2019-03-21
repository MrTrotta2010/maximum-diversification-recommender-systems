#!/bin/bash

#files=("ML-1M" "ML-10M" "ML-20M" "Amazon/VideoGames/v=5" "Amazon/VideoGames/v=10" "Amazon/Clothes/v=5" "Amazon/Clothes/v=10" "Yahoo/Movies")
files=("ML-Latest/later2012")

for f in "${files[@]}" 
do
	
	# users in each ramp-up set
	if [ -z $f ]; then
		echo "Você tem de entrar com um dataset válido"
  		exit
	elif [ $f = "ML-1M" ]; then
		usersTest=1277
		itemsTrain=3682
		percentage=0.08
	elif [ $f = "ML-10M" ]; then
		usersTest=10633
		itemsTrain=10677
		percentage=0.05
	elif [ $f = "ML-20M" ]; then
		usersTest=28704
		itemsTrain=24070
		percentage=0.04
	elif [ $f = "ML-Latest-100k" ]; then
		usersTest=135
		itemsTrain=8375
		percentage=0.06
	elif [ $f = "ML-Latest" ]; then
		usersTest=
		itemsTrain=
		percentage=0.03
	elif [ $f = "ML-Latest/later2012" ]; then
		usersTest=
		itemsTrain=
		percentage=0.03
	elif [ $f = "Amazon/VideoGames/v=5" ]; then
		usersTest=6206
		itemsTrain=45362
		percentage=0.03
	elif [ $f = "Amazon/VideoGames/v=10" ]; then
		usersTest=1612
		itemsTrain=34644
		percentage=0.04
	elif [ $f = "Amazon/Clothes/v=5" ]; then
		usersTest=37198
		itemsTrain=535335
		percentage=0.01
	elif [ $f = "Amazon/Clothes/v=10" ]; then
		usersTest=8376
		itemsTrain=394773
		percentage=0.02
	elif [ $f = "Yahoo/Movies" ]; then
		usersTest=1528
		itemsTrain=10710
		percentage=0.02
	elif [ $f = "CiaoDVD" ]; then
		usersTest=3523
		itemsTrain=16121
		percentage=0.03
	else
  		echo "Você tem de entrar com um parâmetro válido"
	fi
	
	echo "----------------------------------"
	echo "Dataset " $f
	echo "----------------------------------"

#	python ./$f/networkcentroid.py -t ../../../../../Datasets/Ramp-up/$f/trainSet.txt -s ../../../../../Datasets/Ramp-up/$f/testSet.txt -c ../../niche\ of\ users/$f/niches.txt -r NONE -p $percentage -o ../../recommendations/$f/

# TO ML-Latest
	time python ./runNonPersonalized.py -t ../../../../../../../../Nicollas/Researches/Recommender\ Systems/Datasets/$f/trainSet.txt -s ../../../../../../../../Nicollas/Researches/Recommender\ Systems/Datasets/$f/trainSet.txt -c ../../niche\ of\ users/$f/niches.txt -r NONE -p $percentage -o ../../recommendations/$f/

done