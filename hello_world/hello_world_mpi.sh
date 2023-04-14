#!/bin/bash

# SLURM information
#SBATCH -t 00:05:00
#SBATCH -n 4
#SBATCH --mem=5g
#SBATCH -p batch
#SBATCH -J HelloWorldMPIJob