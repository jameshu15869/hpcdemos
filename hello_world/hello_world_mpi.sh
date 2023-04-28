#!/bin/bash

# SLURM information
#SBATCH -t 00:05:00
#SBATCH -n 4
#SBATCH --mem=4g
#SBATCH -p batch
#SBATCH -J HelloWorldMPIJob

#SBATCH -o HelloWorldMPI-%j.out
#SBATCH -e HelloWorldMPI-%j.err

module load mpi

make hello_world_mpi
echo

echo "######### OUTPUT #########"
srun --mpi=pmix ./hello_world_mpi
echo

make clean
