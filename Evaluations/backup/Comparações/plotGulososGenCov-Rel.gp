reset
# set term png 18	#formato da saida do grafico
set term postscript eps 35 enhanced color #formato da saida do grafico
set   autoscale                        # scale axes automatically
#set xtic auto                         # set xtics automatically - distancia dos label
#set ytic auto                           # set ytics automatically
set encoding utf8
#set xtics auto
#set ytics auto
# set yrange [0:60]
set key samplen .5 spacing .9 font ",35"

#set key left bottom
set key at graph 1, 0.98


set output outputFile
#nome de saida
set ylabel "Rel-Genre Coverage" offset 1
set xlabel "Usuários (%)" 
plot inputGuloso using ((column(0) / users) * 100):5 title titleGuloso with line lw 10 lc "yellow",\
    inputGulosoNaive using ((column(0) / users) * 100):5 title titleGulosoNaive with line lw 10 lc "green",\
