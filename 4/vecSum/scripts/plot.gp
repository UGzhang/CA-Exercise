set terminal png
set output "output.png"
set datafile separator ","
set logscale x
set format x "10^{%L}"
set xlabel "ArraySize(KiB)"
set ylabel "AdditionsPerSecond"
set title "Unrolling Performance Analysis"
plot "result_unroll_1.csv" using 1:2 with linespoints title "No Unrolling" linecolor rgb "red", \
     "result_unroll_4.csv" using 1:2 with linespoints title "SSE" linecolor rgb "yellow", \
     "result_unroll_8.csv" using 1:2 with linespoints title "AVX" linecolor rgb "cyan", \
     "result_unroll_16.csv" using 1:2 with linespoints title "AVX 512" linecolor rgb "black"