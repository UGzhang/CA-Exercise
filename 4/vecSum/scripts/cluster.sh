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


for unroll in {2,3,4,8}
do
    make clean -C ../
    make UNROLLTYPE=$unroll -C ../ 


    # This line creates / overrides a result csv file
    echo "ArraySize,AdditionsPerSecond,ActualRuntime,MinimalRuntime" > result_unroll_AVX_$unroll.csv

    STEPS=16
    runtime_ms=1000
    for i in $(seq 0 $((STEPS-1)))
    do

        array_size=$((2 ** i))
        srun ../bin/vecSum $array_size $runtime_ms >> result_unroll_AVX_$unroll.csv

    done

done

gnuplot plot.gp 
