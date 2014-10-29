set autoscale
unset log
unset label
set xtic auto
set ytic auto

set xlabel "Time"
set ylabel "Molecule concentration"

plot "log.dat" using 1:2 title "A" with lines, \
     "log.dat" using 1:3 title "B" with lines
