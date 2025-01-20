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

mem_size=1
echo "AllocatedMem(GiB),MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime,Bx,By" > result_avx256_L1_BxBy.csv
# This line creates / overrides a result csv file

target_product=5000  
bx=2           
growth_rate=1.5   

while [ $bx -le $target_product ]; do
    by=$(echo "scale=0; $target_product / $bx" | bc)

    if [ $by -le 0 ]; then
        break
    fi

    make clean -C ../
    make B_X=$bx B_Y=$by -C ../
    srun ../bin/jacobi $mem_size >> result_avx256_L1_BxBy.csv

    bx=$(echo "$bx * $growth_rate" | bc | awk '{print int($1)}')
done
