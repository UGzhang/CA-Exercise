set terminal png
set output "HIT_RATIO.png"
set datafile separator ","
set logscale x
set xlabel "Memory(KiB)"
set ylabel "L1 HIT RATIO(%)"
set title "MEmory Performance Analysis"
plot "data/result_col_hit_ratio.csv" using 4:3 with linespoints title "Column Wise", \
     "data/result_row_hit_ratio.csv" using 4:3 with linespoints title "Row Wise"
