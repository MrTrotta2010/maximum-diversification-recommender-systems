rec=("userKNN" "itemKNN" "WRMF" "itemAttributeKNN" "softMarginRankingMF" "bestRated" "mostPopular")

#$1 é o dataset

for r in "${rec[@]}" 
do	
	echo $r >> logMDRS.txt
    ./runForAlphas.sh $1 $r

done
