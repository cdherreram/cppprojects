set key b r # leyenda parte de abajo a la derecha
set xlabel 'p'
set ylabel 's'
set title 'Tamaño promedio del cluster percolante más grande s(p,L)'
set term pdf # Guardar en pdf
set out "s.pdf"
plot "datos1.txt" u 2:($1==32?$5:1/0):6  t "L=32"  pt 7 ps 0.3 lc rgb "blue" with errorbars\
   , ''           u 2:($1==64?$5:1/0):6  t "L=64"  pt 7 ps 0.3 lc rgb "red" with errorbars\
   , ''           u 2:($1==128?$5:1/0):6 t "L=128" pt 7 ps 0.3 lc rgb "green" with errorbars\
   , ''           u 2:($1==256?$5:1/0):6 t "L=256" pt 7 ps 0.3 lc rgb "cyan" with errorbars\
   , ''           u 2:($1==512?$5:1/0):6 t "L=512" pt 7 ps 0.3 lc rgb "magenta" with errorbars