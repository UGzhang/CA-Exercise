set terminal png
set output "perf.png"
set datafile separator ","
set logscale x
set xlabel "Memory(KiB)"
set ylabel "MUp/s"
plot "result.csv" using 1:2 with linespoints title "Perfomance-Jacobi"
