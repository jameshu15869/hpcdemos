#!/bin/bash

#SBATCH -t 00:05:00
#SBATCH -n 1
#SBATCH --mem=4g
#SBATCH -p batch
#SBATCH -J HelloWorldSerial

make hello_world_serial
./hello_world_serial