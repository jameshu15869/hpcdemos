#!/bin/bash

#SBATCH -t 00:05:00
#SBATCH -n 1
#SBATCH --mem=4g
#SBATCH -p batch
#SBATCH -J HelloWorldSerial
#SBATCH -o hello_world_serial-%j.out

Help()
{
	echo "Syntax: hello_world_serial [-h]"
	echo "options:"
	echo "h                Print this help"
	echo "-n <numthreads>  Number of threads to run with"
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

make hello_world_serial
echo

echo "######### OUTPUT #########"
./hello_world_serial
echo

make clean
