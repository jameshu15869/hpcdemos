EXECS=add_arrays_serial add_arrays_omp add_arrays_mpi
MPICC?=mpicc

all: ${EXECS}

add_arrays_serial: add_arrays_serial.c
	gcc -fopenmp -o add_arrays_serial add_arrays_serial.c

add_arrays_omp: add_arrays_omp.c
	gcc -fopenmp -o add_arrays_omp add_arrays_omp.c

add_arrays_mpi: add_arrays_mpi.c
	mpicc -o add_arrays_mpi add_arrays_mpi.c

clean: 
	rm -f ${EXECS}