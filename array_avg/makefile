EXECS=array_avg_serial array_avg_omp array_avg_mpi_scatter_gather array_avg_mpi_reduce
MPICC?=mpicc

all: ${EXECS}

array_avg_serial: array_avg_serial.c
	gcc -fopenmp -o array_avg_serial array_avg_serial.c

array_avg_omp: array_avg_omp.c
	gcc -fopenmp -o array_avg_omp array_avg_omp.c

array_avg_mpi_scatter_gather: array_avg_mpi_scatter_gather.c
	mpicc -o array_avg_mpi_scatter_gather array_avg_mpi_scatter_gather.c

array_avg_mpi_reduce: array_avg_mpi_reduce.c
	mpicc -o array_avg_mpi_reduce array_avg_mpi_reduce.c

clean: 
	rm -f ${EXECS}