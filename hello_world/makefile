EXECS=hello_world_serial hello_world_mpi hello_world_omp
MPICC?=mpicc

all: ${EXECS}

hello_world_serial: hello_world_serial.c
	gcc -o hello_world_serial hello_world_serial.c

hello_world_omp: hello_world_omp.c
	gcc -fopenmp -o hello_world_omp hello_world_omp.c

hello_world_mpi: hello_world_mpi.c
	mpicc -o hello_world_mpi hello_world_mpi.c

clean: 
	rm -f ${EXECS}