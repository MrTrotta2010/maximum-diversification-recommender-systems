
#teste=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30)
teste=(1 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100)

for t in "${teste[@]}" 
do	
	sudo rm $2/alfa$1/$3$t/acc.txt
	sort -f -r -k2 $2/alfa$1/$3$t/eval.txt > $2/alfa$1/$3$t/acc.txt
	chmod 777 $2/alfa$1/$3$t/acc.txt
	sudo rm $2/alfa$1/$3$t/acc_rel.txt
	sort -f -r -n -k3 $2/alfa$1/$3$t/eval.txt > $2/alfa$1/$3$t/acc_rel.txt
	chmod 777 $2/alfa$1/$3$t/acc_rel.txt
	sudo rm $2/alfa$1/$3$t/div.txt
	sort -f -r -k4 $2/alfa$1/$3$t/eval.txt > $2/alfa$1/$3$t/div.txt
	chmod 777 $2/alfa$1/$3$t/div.txt
	sudo rm $2/alfa$1/$3$t/div_rel.txt
	sort -f -r -k5 $2/alfa$1/$3$t/eval.txt > $2/alfa$1/$3$t/div_rel.txt
	chmod 777 $2/alfa$1/$3$t/div_rel.txt
done