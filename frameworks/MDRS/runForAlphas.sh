#!/bin/bash

#files=("ML-1M" "ML-10M" "ML-20M" "Amazon/VideoGames/v=5" "Amazon/VideoGames/v=10" "Amazon/Clothes/v=5" "Amazon/Clothes/v=10" "Yahoo/Movies" "ML-Latest/later2012")
alpha=(0.0 0.25 0.5 0.75 1.0)

for a in "${alpha[@]}" 
do	
	echo "Alpha: " $a
    ./mdrs $a

done

