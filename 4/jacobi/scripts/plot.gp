set terminal png
set output "perf.png"
set datafile separator ","
set logscale x
set xlabel "Memory(KiB)"
set ylabel "MUp/s"
set title "Unrolling Performance Analysis"
plot "result_unroll_1.csv" using 1:2 with linespoints title "No Unrolling" linecolor rgb "red", \
     "result_unroll_2.csv" using 1:2 with linespoints title "SSE" linecolor rgb "blue", \
     "result_unroll_4.csv" using 1:2 with linespoints title "AVX" linecolor rgb "green", \
     "result_unroll_8.csv" using 1:2 with linespoints title "AVX512" linecolor rgb "cyan"
