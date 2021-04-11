reset

set terminal pngcairo

set style line 1 lc rgb 'red' lt 1 lw 2 pt 7 ps 2
set style line 2 lc rgb 'magenta' lt 1 lw 2 pt 7 ps 2

unset key
unset tics
set border 0
set xrange[0:30]
set yrange[0:30]

system('mkdir -p png')
n = 0
do for [ii=3:7]{
   n = n+1
   set output sprintf('png/file%03.0f.png',n)
   #plot 'datos.txt' u 2:3 w p ls 1
   #plot 'datos.txt' u 5:6 w p ls 2
   #plot 'datos.txt' u 8:9 w p ls 1
   #plot for [jj=2:20:3] 'datos.txt' using jj:(column(jj-1) == 1 ? column(jj+1):1/0) every ::ii::ii w p ls 1 #,\
   plot for [jj=2:20:3] 'datos.txt' using jj:column(jj+1) every ::ii::ii w p ls 1
   #plot for [jj=2:20:3] 'datos.txt' using jj:(column(jj-1) == 1 ? column(jj+1):1/0) every ::ii::ii w p ls 1 #,\
   #'datos.txt' using jj:(column(jj-1) != 1 ? column(jj+1):1/0) every ::ii::ii w p ls 2
} 
