#$1 é a base
#$2 é o número de usuários

metrics=('Prec' 'Prec-Rel' 'GenCov' 'GenCov-Rel')

for m in "${metrics[@]}"
do

	echo $m

	gnuplot -e "outputFile='$1/PlotsGulosos/plot$m'; inputGuloso='$1/Guloso/$m.txt'; inputGulosoNaive='$1/GulosoNaive/$m.txt'; titleGuloso='Guloso'; titleGulosoNaive='Guloso Naive'; users=$2" plotGulosos$m.gp

done