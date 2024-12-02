set terminal png
set output "output-1-2.png"
set datafile separator ","
set logscale x
set xlabel "ActualRuntime"
set ylabel "AdditionsPerSecond"
plot "result-1-2.csv" using 3:2 with linespoints title "Perfomance(ArraySize 512KiB)"


set output "output-1-3.png"
set datafile separator ","
set logscale x
set format x "10^{%L}"
set xlabel "ArraySize(Byte)"
set ylabel "AdditionsPerSecond"
plot "result-1-3.csv" using 1:2 with linespoints title "Perfomance(MiniRun 1000ms)"