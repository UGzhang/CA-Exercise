set terminal png
set output "output.png"
set datafile separator ","
set logscale x
set format x "10^{%L}"
set xlabel "ArraySize(KiB)"
set ylabel "AdditionsPerSecond"
set title "Unrolling Performance Analysis"
plot "result_unroll_AVX_2.csv" using 1:2 with linespoints title "unroll_AVX_2" linecolor rgb "red", \
     "result_unroll_AVX_3.csv" using 1:2 with linespoints title "unroll_AVX_3" linecolor rgb "yellow", \
     "result_unroll_AVX_4.csv" using 1:2 with linespoints title "unroll_AVX_4" linecolor rgb "cyan", \
     "result_unroll_AVX_8.csv" using 1:2 with linespoints title "unroll_AVX_8" linecolor rgb "black"