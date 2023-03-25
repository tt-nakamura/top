reset
#set terminal aqua
set terminal postscript eps enhanced 24
set output "fig3.eps"
set xlabel "t  / sec"
set ylabel "{/Symbol q}  / deg"
set xrange [0:15]
set yrange [0:180]
set key left Left reverse
plot \
"fig3a.txt" u 1:2 t "{/Symbol m}_0 = 0.1" w l lt 1 lc 1 lw 1,\
"fig3a.txt" u 1:($2/$3) not w l lt 1 lc 1 lw 5,\
"fig3b.txt" u 1:2 t "        0.05" w l lt 1 lc 2 lw 1,\
"fig3b.txt" u 1:($2/$3) not w l lt 1 lc 2 lw 5,\
"fig3c.txt" u 1:2 t "        0.01" w l lt 1 lc 3 lw 1,\
"fig3c.txt" u 1:($2/$3) not w l lt 1 lc 3 lw 5
