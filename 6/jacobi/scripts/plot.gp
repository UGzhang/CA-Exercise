set terminal png
set output "perf.png"
set datafile separator ","
set logscale x
set xlabel "Memory(GiB)"
set ylabel "MUp/s"
set title "Performance Analysis"
plot "result_avx256.csv" using 1:2 with linespoints title "No Spatial Blocking", \
     "result_avx256_L1.csv" using 1:2 with linespoints title "Spatial Blocking = 1228", \
     "result_avx256_L2.csv" using 1:2 with linespoints title "Spatial Blocking = 32768"