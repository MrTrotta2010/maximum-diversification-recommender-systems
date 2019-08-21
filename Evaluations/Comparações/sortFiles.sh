#$1 é a base

algoritmo=('PSO' 'ITS' 'Guloso' 'GulosoNaive' 'userKNN')

for a in "${algoritmo[@]}"
do 
	cd $1/$a
	sudo rm Prec.txt
	sort -f -r -k2 eval.txt > Prec.txt
	chmod 777 Prec.txt
	sudo rm Prec-Rel.txt
	sort -f -r -n -k3 eval.txt > Prec-Rel.txt
	chmod 777 Prec-Rel.txt
	sudo rm GenCov.txt
	sort -f -r -n -k4 eval.txt > GenCov.txt
	chmod 777 GenCov.txt
	sudo rm GenCov-Rel.txt
	sort -f -r -n -k5 eval.txt > GenCov-Rel.txt
	chmod 777 GenCov-Rel.txt
	cd ../../
done