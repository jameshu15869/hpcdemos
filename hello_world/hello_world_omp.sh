#!/bin/bash

#SBATCH -t 00:05:00
#SBATCH -n 4
#SBATCH --mem=4G
#SBATCH -J MyOMPJob

#SBATCH -o %x-%j.out
#SBATCH -e %x-%j.err

#SBATCH -p batch

Help()
{
	echo "Syntax: hello_world_mpi [-h|-n <numthreads]"
	echo "options:"
	echo "	-h		Print this help"
	echo "	-n <numthreads>	Number of threads to run with"
	echo
}

N_THREADS=1
while getopts ":hn:" options; do
	case "${options}" in
		h) #display Help
			Help
			exit;;
		n) # pass in num cores
			N_THREADS=${OPTARG};;
		:) # missing optarg
			N_THREADS=0;;
		\?) #invalid option
			echo "Error: Invalid option"
			exit;;
	esac
done

if [ "$N_THREADS" -eq "0" ]; then
	echo "num threads  -n must be provided"
	exit
fi

echo ${N_THREADS}
export OMP_NUM_THREADS=${N_THREADS}
make hello_world_omp
echo

echo "######### OUTPUT #########"
./hello_world_omp
echo

make clean
