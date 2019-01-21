datasets=("ML-1M" "CIAO")

sudo rm logMDRS.txt

for d in "${datasets[@]}" 
do	
	echo "----------------------------------" >> logMDRS.txt
	echo "Dataset " $d >> logMDRS.txt
	echo "----------------------------------" >> logMDRS.txt
    ./runForAllRecommenders.sh $d
	echo "----------------------------------" >> logMDRS.txt

done
