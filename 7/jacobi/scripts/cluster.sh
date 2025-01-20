#!/bin/bash -l
  
#SBATCH --partition=singlenode
#SBATCH --time=00:10:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --exclusive
#SBATCH --cpu-freq=2400000-2400000:performance
#SBATCH --export=NONE

# Enable debug and verbose mode
set -x
set -v

# To ensure 'srun' runs as expected
export SLURM_EXPORT_ENV=ALL
export SRUN_CPUS_PER_TASK=1  # value should match the SBATCH --cpus-per-task option

# B_X: blocking factor
module load intel

# execute measurement with for loop
# 18 measurement points, exponentially distributed: 1 KiB (2^10 B) - 128 GiB (2^37 B), each with 1000 ms set as the minimal runtime.
# results should be appended to the result.csv (see '>>' operator)

STEPS=7
mem_size=1

echo "AllocatedMem(MiB),MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" > result_avx256.csv
# This line creates / overrides a result csv file



make clean -C ../
make B_X=216 B_Y=25 -C ../


for i in $(seq 0 $((STEPS-1)))
do

    mem_size=$(echo "scale=2; 2 ^ $i" | bc)
    srun ../bin/jacobi $mem_size  >> result_avx256.csv

done


gnuplot plot.gp 