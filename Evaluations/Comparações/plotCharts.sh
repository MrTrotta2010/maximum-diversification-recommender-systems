metrics=('Prec' 'Prec-Rel' 'GenCov' 'GenCov-Rel')

for m in "${metrics[@]}"
do

	echo $m

	gnuplot -e "outputFile='Plots/plot$m'; inputPSO='PSO/$m.txt'; inputITS='ITS/$m.txt'; inputGuloso='Guloso/$m.txt'; titlePSO='PSO 100'; titleITS='ITS 100-1000'; titleGuloso='Guloso'" plot$m.gp

done