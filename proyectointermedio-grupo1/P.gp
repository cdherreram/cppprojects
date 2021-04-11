set key b r # leyenda parte de abajo a la derecha
set xlabel 'p'
set ylabel 'P'
set title 'Probabilidad P(p,L) de que exista un percolante'
set term pdf # Guardar en pdf
set out "P.pdf"
plot "datos1.txt" u 2:($1==32?$3:1/0):4  t "L=32"  pt 7 ps 0.3 lc rgb "blue" with errorbars\
   , ''           u 2:($1==64?$3:1/0):4  t "L=64"  pt 7 ps 0.3 lc rgb "red" with errorbars\
   , ''           u 2:($1==128?$3:1/0):4 t "L=128" pt 7 ps 0.3 lc rgb "green" with errorbars\
   , ''           u 2:($1==256?$3:1/0):4 t "L=256" pt 7 ps 0.3 lc rgb "cyan" with errorbars\
   , ''           u 2:($1==512?$3:1/0):4 t "L=512" pt 7 ps 0.3 lc rgb "magenta" with errorbars