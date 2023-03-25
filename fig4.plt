reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig4.eps"
set xlabel "t  / sec"
set ylabel "{/Symbol q}  / deg"
set xrange [0:3]
set yrange [0:3]
plot \
"fig4a.txt" u 1:2 t "{/Symbol w}_0 = 0.087 rad/s" w l lt 1 lc 1 lw 1,\
"fig4a.txt" u 1:($2/$3) not w l lt 1 lc 1 lw 5,\
"fig4b.txt" u 1:2 t "0.043         " w l lt 1 lc 2 lw 1,\
"fig4c.txt" u 1:2 t "0.022         " w l lt 1 lc 3 lw 1
