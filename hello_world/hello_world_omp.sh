#!/bin/bash

#SBATCH -t 00:05:00
#SBATCH -n 4
#SBATCH --mem=4G
#SBATCH -J MyOMPJob

#SBATCH -o %x-%j.out
#SBATCH -e %x-%j.err

#SBATCH -p batch

if [[ -n "${OMP_NUM_THREADS}" ]]; then
	:
else
	export OMP_NUM_THREADS=1
fi

make hello_world_omp
./hello_world_omp
make clean
