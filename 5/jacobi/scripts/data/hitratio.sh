#!/bin/bash -l


STEPS=18
mem_size=1

OUTPUT_FILE_ROW="data/result_row_hit_ratio.csv"
echo "LOADS,HITS,HIT_RATIO,ARRAY_SIZE" > "$OUTPUT_FILE_ROW"


for i in $(seq 0 $((STEPS-1)))
do
    INPUT_FILE="data/likwid_analysis_row_$i.csv"
    LOADS=$(grep "MEM_LOAD_RETIRED_L1_ALL" "$INPUT_FILE" | cut -d , -f 3)
    HITS=$(grep "MEM_LOAD_RETIRED_L1_HIT" "$INPUT_FILE" | cut -d , -f 3)
    #divide corresponding elements of HITS by LOADS
    HIT_RATIO=$(paste -d',' <(echo "$HITS") <(echo "$LOADS") | awk -F',' '{if ($2 != 0) print $1/$2*100; else print "NaN"}')
    ARRAY_SIZES=$((2 ** i))
    echo $LOADS,$HITS,$HIT_RATIO,$ARRAY_SIZES >> "$OUTPUT_FILE_ROW"
done

OUTPUT_FILE_COL="data/result_col_hit_ratio.csv"
echo "LOADS,HITS,HIT_RATIO,ARRAY_SIZE" > "$OUTPUT_FILE_COL"

for i in $(seq 0 $((STEPS-1)))
do
    INPUT_FILE="data/likwid_analysis_col_$i.csv"
    LOADS=$(grep "MEM_LOAD_RETIRED_L1_ALL" "$INPUT_FILE" | cut -d , -f 3)
    HITS=$(grep "MEM_LOAD_RETIRED_L1_HIT" "$INPUT_FILE" | cut -d , -f 3)
    #divide corresponding elements of HITS by LOADS
    HIT_RATIO=$(paste -d',' <(echo "$HITS") <(echo "$LOADS") | awk -F',' '{if ($2 != 0) print $1/$2*100; else print "NaN"}')
    ARRAY_SIZES=$((2 ** i))
    echo $LOADS,$HITS,$HIT_RATIO,$ARRAY_SIZES >> "$OUTPUT_FILE_COL"
done

