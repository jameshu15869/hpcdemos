EXECS=pi_serial pi_omp pi_mpi
MPICC?=mpicc

all: ${EXECS}

pi_serial: pi_serial.c
	gcc -fopenmp -o pi_serial pi_serial.c

pi_omp :pi_omp.c
	gcc -fopenmp -o pi_omp pi_omp.c

pi_mpi : pi_mpi.c
	${MPICC} -o pi_mpi pi_mpi.c

clean:
	rm -f pi_serial pi_omp pi_mpi