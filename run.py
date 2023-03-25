import sys
import os
import subprocess

programs = {
    'hello_world_demo': ("hello_world", [
        "./hello_world/hello_world_serial",
        "./hello_world/hello_world_omp",
        "mpirun -n 2 ./hello_world/hello_world_mpi"
    ]),
    "pi" : ("pi", [
        "./pi/pi_serial",
        "./pi/pi_omp",
        "mpirun -n 2 ./pi/pi_mpi"
    ]),
    "add_arrays" : ("add_arrays", [
        "./add_arrays/add_arrays_serial",
        "./add_arrays/add_arrays_omp",
        "mpirun -n 2 ./add_arrays/add_arrays_mpi"
    ]),
    "array_avg" : ("array_avg", [
        "./array_avg/array_avg_serial",
        "./array_avg/array_avg_omp",
        "mpirun -n 2 ./array_avg/array_avg_mpi_scatter_gather",
        "mpirun -n 2 ./array_avg/array_avg_mpi_reduce"
    ]),
}

program_to_run = sys.argv[1] if len(sys.argv) > 1 else None
if not program_to_run in programs:
    print('Must enter a valid program name. Possible programs: {0}'.format(programs.keys()))

else:
    with open(os.devnull, "wb") as devnull:
        subprocess.call(["cd ./{0} && make".format(programs[program_to_run][0])],
        stdout=devnull, stderr=subprocess.STDOUT, shell=True)
    
    for sys_call in programs[program_to_run][1]:
        print("\033[92m {0}\033[00m" .format(sys_call))
        subprocess.call([sys_call], shell=True)
        print()