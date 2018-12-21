recs=("itemKNN" "userKNN" "WRMF")

for r in "${recs[@]}";
do

	cd $r

	sudo rm acc.txt
	sort -f -r -k2 eval.txt > acc.txt
	chmod 777 acc.txt
	sudo rm acc_Rel.txt
	sort -f -r -k3 eval.txt > acc_Rel.txt
	chmod 777 acc_Rel.txt
	sudo rm div.txt
	sort -f -r -k4 eval.txt > div.txt
	chmod 777 div.txt
	sudo rm div_rel.txt
	sort -f -r -k5 eval.txt > div_rel.txt
	chmod 777 div_rel.txt

	#gnuplot plotEval.gp
	#chmod 777 acc.eps
	#chmod 777 accRel.eps
	#chmod 777 div.eps

	cd ..
	echo "output: $r"

done

cd ..
