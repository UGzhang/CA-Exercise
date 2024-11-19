set terminal png
set output "output.png"
set datafile separator ","
set logscale x
set format x "10^{%L}"
set xlabel "ArraySize(KiB)"
set ylabel "AdditionsPerSecond"
set title "Unrolling Performance Analysis"
plot "result_unroll_1.csv" using 1:2 with linespoints title "No Unrolling" linecolor rgb "red", \
     "result_unroll_2.csv" using 1:2 with linespoints title "Unrolling = 2" linecolor rgb "blue", \
     "result_unroll_3.csv" using 1:2 with linespoints title "Unrolling = 3" linecolor rgb "green", \
     "result_unroll_4.csv" using 1:2 with linespoints title "Unrolling = 4" linecolor rgb "yellow", \
     "result_unroll_8.csv" using 1:2 with linespoints title "Unrolling = 8" linecolor rgb "cyan", \
     "result_unroll_16.csv" using 1:2 with linespoints title "Unrolling = 16" linecolor rgb "black"