set datafile separator ','
set term png size 800, 800
set output "figure.png"
set multiplot

set size 1, 0.5
set title 'Acceleration'
set ylabel "Acceleration (m/s^2)" # label for the Y axis
set xlabel "Time (seconds)" # label for the X axis
set origin 0.0,0.5

plot 'output.csv' using 1:2 with lp t 'Acceleration'

set size 1, 0.5
set title 'Velocity'
set ylabel "Velocity (m/s)" # label for the Y axis
set xlabel "Time (seconds)" # label for the X axis
set origin 0.0,0.0

plot 'output.csv' using 1:3 with lp t 'Velocity'

unset multiplot