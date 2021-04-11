#!/usr/bin/gnuplot
#
# Generate an animated spiral
#
# AUTHOR: Hagen Wierstorf

reset

# png
set terminal pngcairo size 750,750 enhanced square font 'Verdana,10'

# color definitions
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1 # --- blue
set style line 2 lc rgb 'black' lt 1 lw 2 pt 7 ps 1 # --- black
set style line 3 lc rgb 'red' lt 1 lw 2 pt 7 ps 1 # --- red
set style line 4 lc rgb 'magenta' lt 1 lw 2 pt 7 ps 1 # --- blue
set style line 5 lc rgb 'gold' lt 1 lw 2 pt 7 ps 1 # --- blue
set style line 6 lc rgb 'green' lt 1 lw 2 pt 7 ps 1 # --- blue
set style line 7 lc rgb 'gray' lt 1 lw 2 pt 7 ps 1 # --- blue
set style line 8 lc rgb '#cb4679' lt 1 lw 2 pt 7 ps 1 # --- magenta
set style line 9 lc rgb 'purple' lt 1 lw 2 pt 7 ps 1 # --- blue
set style line 10 lc rgb '#21908d' lt 1 lw 2 pt 7 ps 1 # --- lime-green

unset key
set size ratio 1
set border 15 back lw 1
unset tics
set view 342,0
set xrange [-7.2:17.8]
set yrange [-8.8:17.8]

system('mkdir -p png')
# spiral upwards

n=0
y0=0
do for [ii=15:287] {
    n=n+1
    set output sprintf('png/dinamica%03.0f.png',n)
    set multiplot layout 2,2 rowsfirst
    set xrange [-10.2:17.8]
    set yrange [-8.8:17.8]
    set border 15 back lw 1 lc rgb 'black'
    plot for [jj=3:199:4] 'data15.txt' u jj:((column(jj-2)==1 && column(jj-1)==0) ? column(jj+1):1/0) every ::ii::ii w p ls 1,\
         for [jj=3:199:4] 'data15.txt' u jj:((column(jj-2)==1 && column(jj-1)==1) ? column(jj+1):1/0) every ::ii::ii w p ls 3,\
         for [jj=3:199:4] 'data15.txt' u jj:((column(jj-2)==1 && column(jj-1)==2) ? column(jj+1):1/0) every ::ii::ii w p ls 6
    
    set xrange [-7.2:32.8]
    set yrange [-10.8:32.8]
    set border 15 back lw 1 lc rgb 'red'
    plot for [jj=3:199:4] 'data15.txt' u jj:((column(jj-1)==1 && column(jj-2)==0) ? column(jj+1):1/0) every ::ii::ii w p ls 3,\
         for [jj=3:199:4] 'data15.txt' u jj:((column(jj-1)==2 && column(jj-2)==0) ? column(jj+1):1/0) every ::ii::ii w p ls 6
    
    set xrange [-10.2:17.8]
    set yrange [-8.8:17.8]
    set border 15 back lw 1 lc rgb 'black'
    plot for [jj=3:199:4] 'data15.txt' u jj:((column(jj-1)==0 && column(jj-2)==2) ? column(jj+1):1/0) every ::ii::ii w p ls 1,\
         for [jj=3:199:4] 'data15.txt' u jj:((column(jj-1)==1 && column(jj-2)==2) ? column(jj+1):1/0) every ::ii::ii w p ls 3,\
         for [jj=3:199:4] 'data15.txt' u jj:((column(jj-1)==2 && column(jj-2)==2) ? column(jj+1):1/0) every ::ii::ii w p ls 6
   
    set xrange [-10.2:17.8]
    set yrange [-8.8:17.8]
    set border 15 back lw 1 lc rgb 'black'
    plot for [jj=3:199:4] 'data15.txt' u jj:((column(jj-2)==3 && column(jj-1)==0) ? column(jj+1):1/0) every ::ii::ii w p ls 1,\
         for [jj=3:199:4] 'data15.txt' u jj:((column(jj-2)==3 && column(jj-1)==1) ? column(jj+1):1/0) every ::ii::ii w p ls 3,\
         for [jj=3:199:4] 'data15.txt' u jj:((column(jj-2)==3 && column(jj-1)==2) ? column(jj+1):1/0) every ::ii::ii w p ls 6 



    unset multiplot
    
    }


