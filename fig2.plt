reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig2.eps"
set xlabel "t  / sec"
set ylabel "{/Symbol q}  / deg"
set xrange [0:15]
set yrange [0:35]
plot \
"fig2a.txt" u 1:2 t "{/Symbol m}_0 = 0.01, {/Symbol w}_0 = 200 rad/s" w l lt 1 lc 1 lw 1,\
"fig2a.txt" u 1:($2/$3) not w l lt 1 lc 1 lw 5,\
"fig2b.txt" u 1:2 t "0.02,         200         " w l lt 1 lc 2 lw 1,\
"fig2b.txt" u 1:($2/$3) not w l lt 1 lc 2 lw 5,\
"fig2c.txt" u 1:2 t "0.01,         300         " w l lt 1 lc 3 lw 1,\
"fig2c.txt" u 1:($2/$3) not w l lt 1 lc 3 lw 5,\
"fig2d.txt" u 1:2 t "0.02,         300         " w l lt 1 lc 4 lw 1,\
"fig2d.txt" u 1:($2/$3) not w l lt 1 lc 4 lw 5
