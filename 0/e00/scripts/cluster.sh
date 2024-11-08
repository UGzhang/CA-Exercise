#!/bin/bash -l
  
#SBATCH --partition=singlenode
#SBATCH --time=00:00:30
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --export=NONE

# The script runtime should be less than one millisecond so we choose a very short time for resource allocation (--time parameter).
# Note that the invocation overhead of the bash script might also take some time.

# Enable debug and verbose mode
set -x
set -v

# To ensure 'srun' runs as expected
export SLURM_EXPORT_ENV=ALL
export SRUN_CPUS_PER_TASK=1  # Value should match the SBATCH --cpus-per-task option

srun ../bin/hello  # Path depends on the current working directory and may needs to be updated
