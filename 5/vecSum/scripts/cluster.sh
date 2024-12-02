#!/bin/bash -l
  
#SBATCH --partition=singlenode
#SBATCH --time=00:08:00
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


module load likwid hwloc

lstopo --of svg > fritz.svg

make clean -C ../
make -C ../


# TODO 1.2 Run benchmark with varying runtime and fixed array size
# execute measurement with for loop over exponentially distributed runtime: 1ms - 10s , each run with 512 KiB set as the array size.
# Choose a reasonable number of measurement points.
# results should be appended to the result.csv (see '>>' operator)

runtime_ms=1
array_size=512

# This line creates / overrides a result csv file
echo "ArraySize,AdditionsPerSecond,ActualRuntime,MinimalRuntime" > result-1-2.csv

while [ $runtime_ms -le 10000 ]
do
    srun ../bin/vecSum  $array_size $runtime_ms >> result-1-2.csv
    runtime_ms=$(( runtime_ms * 2 ))
    
done



# TODO 1.3 Run benchmark with varying array sizes and fixed runtime
# execute measurement with for loop
# 16 measurement points, exponentially distributed: 1 KiB (2^10 B) - 32 MiB (2^25 B), each with 1000 ms set as the minimal runtime.
# results should be appended to the result.csv (see '>>' operator)
# srun ../bin/vecSum ...


# Since we want to plot the data in upcoming exercises we benefit from a flexible resolution on the step size.
# Increase the number of measurement points from 16 to 30 or higher.
# Add a STEPS variable which specifies this number of measurement points
# Hint: the use of 'awk', 'bc' or a similar program might be helpful to calculate math expressions.
# Hint: you can write a bash function which retrieves the current step and total number of steps and returns the KiB 

runtime_ms=1000
STEPS=16

# This line creates / overrides a result csv file
echo "ArraySize,AdditionsPerSecond,ActualRuntime,MinimalRuntime" > result-1-3.csv

for i in $(seq 0 $((STEPS-1)))
do

    array_size=$((2 ** i))
    srun ../bin/vecSum $array_size $runtime_ms >> result-1-3.csv

done


gnuplot plot.gp 
