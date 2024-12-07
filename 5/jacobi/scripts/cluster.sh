#!/bin/bash -l
  
#SBATCH --partition=singlenode
#SBATCH --time=00:06:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --exclusive
#SBATCH --cpu-freq=2400000-2400000:performance
#SBATCH --export=NONE
#SBATCH -C hwperf

# Enable debug and verbose mode
set -x
set -v

# To ensure 'srun' runs as expected
export SLURM_EXPORT_ENV=ALL
export SRUN_CPUS_PER_TASK=1  # value should match the SBATCH --cpus-per-task option


module load intel likwid/5.3.0
make clean -C ../
make -C ../ WISE=ROW

gprof ../bin/jacobi ./gmon.out > gprof_analysis.txt

STEPS=18
mem_size=1

# row
echo "AllocatedMem,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" > data/result_row.csv

for i in $(seq 0 $((STEPS-1)))
do
    mem_size=$((2 ** i))
    likwid-perfctr -o data/likwid_analysis_row_$i.csv -C 0 -c 0 -f -m -g MEM_LOAD_RETIRED_L1_ALL:PMC1,MEM_LOAD_RETIRED_L1_HIT:PMC2,MEM_LOAD_RETIRED_L2_ALL:PMC3,MEM_LOAD_RETIRED_L2_HIT:PMC4,MEM_LOAD_RETIRED_L3_ALL:PMC5,MEM_LOAD_RETIRED_L3_HIT:PMC6 ../bin/jacobi $mem_size >> data/result_row.csv
done

make clean -C ../
make -C ../ WISE=COLUMN

# column
echo "AllocatedMem,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" > data/result_column.csv

for i in $(seq 0 $((STEPS-1)))
do
    mem_size=$((2 ** i))
    likwid-perfctr -o data/likwid_analysis_col_$i.csv -C 0 -c 0 -f -m -g MEM_LOAD_RETIRED_L1_ALL:PMC1,MEM_LOAD_RETIRED_L1_HIT:PMC2,MEM_LOAD_RETIRED_L2_ALL:PMC3,MEM_LOAD_RETIRED_L2_HIT:PMC4,MEM_LOAD_RETIRED_L3_ALL:PMC5,MEM_LOAD_RETIRED_L3_HIT:PMC6 ../bin/jacobi $mem_size >> data/result_column.csv
done

data/hitratio.sh
gnuplot data/plot.gp


