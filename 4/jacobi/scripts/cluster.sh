#!/bin/bash -l
  
#SBATCH --partition=singlenode
#SBATCH --time=00:08:00
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


module load intel

for unroll in {1,2,4,8,16}
do
make clean -C ../
make UNROLLTYPE=${unroll} -C ../

# execute measurement with for loop
# 18 measurement points, exponentially distributed: 1 KiB (2^10 B) - 128 MiB (2^27 B), each with 1000 ms set as the minimal runtime.
# results should be appended to the result.csv (see '>>' operator)

STEPS=18
mem_size=1
echo "AllocatedMem,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" > result_unroll_$unroll.csv

# This line creates / overrides a result csv file

for i in $(seq 0 $((STEPS-1)))
do

    mem_size=$((2 ** i))
    srun ../bin/jacobi $mem_size  >> result_unroll_$unroll.csv

done
done
gnuplot plot.gp 