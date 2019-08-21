#$1 é a base
#$2 é o número de usuários

metrics=('Prec' 'Prec-Rel' 'GenCov' 'GenCov-Rel')

for m in "${metrics[@]}"
do

	echo $m

	gnuplot -e "outputFile='$1/Plots/plot$m'; inputPSO='$1/PSO/$m.txt'; inputITS='$1/ITS/$m.txt'; inputGuloso='$1/Guloso/$m.txt'; inputGulosoNaive='$1/GulosoNaive/$m.txt'; inputBase='$1/userKNN/$m.txt'; titlePSO='PSO 100'; titleITS='ITS 100-1000'; titleGuloso='Guloso'; titleGulosoNaive='Guloso Naive'; titleBase='UserKNN'; users=$2" plot$m.gp

done
