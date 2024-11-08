#!/bin/bash -l
  
#SBATCH --partition=singlenode
#SBATCH --time=00:05:00
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

# This line creates / overrides a result csv file
echo "ArraySize,AdditionsPerSecond,ActualRuntime,MinimalRuntime" > result.csv


# TODO 1.2 Run benchmark with varying runtime and fixed array size
# execute measurement with for loop over exponentially distributed runtime: 1ms - 10s , each run with 512 KiB set as the array size.
# Choose a reasonable number of measurement points.
# results should be appended to the result.csv (see '>>' operator)
# srun ../bin/vecSum ...

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
