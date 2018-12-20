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


set output "../Results/UserKNN/acc.eps"		#nome de saida
set ylabel "Acurácia" offset 1
set xlabel "Usuários (%)" 
plot "../MDRS_Output/ML-1M/alfa0.000000/userKNN/acc.txt" using ((column(0) / 6040) * 100):2 title "MDRS a=0" with line lw 10 lc "#000000",\
    "../Standard/userKNN/acc.txt" using ((column(0) / 6040) * 100):2 title "UserKNN" with line lw 10 lc "red",\


set output "../Results/UserKNN/accRel.eps"		#nome de saida
set ylabel "Acurácia com Relevância" offset 1
set xlabel "Usuários (%)" 
plot "../MDRS_Output/ML-1M/alfa0.000000/userKNN/acc_Rel.txt" using ((column(0) / 6040) * 100):3 title "MDRS a=0" with line lw 10 lc "#000000",\
    "../Standard/userKNN/acc_Rel.txt" using ((column(0) / 6040) * 100):3 title "UserKNN" with line lw 10 lc "red",\

set output "../Results/UserKNN/div.eps"		#nome de saida
set ylabel "Diversidade" offset 1
set xlabel "Usuários (%)" 
plot "../MDRS_Output/ML-1M/alfa0.000000/userKNN/div.txt" using ((column(0) / 6040) * 100):4 title "MDRS a=0" with line lw 10 lc "#000000",\
    "../Standard/userKNN/div.txt" using ((column(0) / 6040) * 100):4 title "UserKNN" with line lw 10 lc "red",\

set output "../Results/UserKNN/divRel.eps"		#nome de saida
set ylabel "Diversidade" offset 1
set xlabel "Usuários (%)" 
plot "../MDRS_Output/ML-1M/alfa0.000000/userKNN/div_rel.txt" using ((column(0) / 6040) * 100):5 title "MDRS a=0" with line lw 10 lc "#000000",\
    "../Standard/userKNN/div_rel.txt" using ((column(0) / 6040) * 100):5 title "UserKNN" with line lw 10 lc "red",\
