reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig1.eps"
set xlabel "t  / sec"
set ylabel "y  / cm"
set xrange [0:6]
set yrange [0:40]
set key bottom right
plot \
"fig1.txt" u 1:2 t "rolling" w l lt 1 lw 1,\
"fig1.txt" u 1:($2/$3) t "sliding" w l lt 1 lw 5
