from mpi4py import MPI
import math
import random
import sys

#TO RUN: mpiexec -np 4 python3 MPI_vector_dot.py 20

def print_vector(vector, size):
    index = 0
    while index < size:
        print(vector[index]," ",end='')
        index += 1
    print("\n")

def randomize_vector(vector, size):
    index = 0
    while index < size:
        vector.append(random.uniform(0,10))
        #use random.random() for decimals between 0-1.
        index +=1
    return vector

def main(argv):
    comm = MPI.COMM_WORLD
    processors = comm.Get_size()
    rank = comm.Get_rank()

    SIZE = int(sys.argv[1])
    slice_size = SIZE//processors
    my_vector = []
    vector2 = []

    if SIZE%processors == 0:
        my_vector = randomize_vector(my_vector, SIZE)
        local_sum = 0
        global_sum = 0

        print_vector(my_vector,slice_size)

        i = 0
        while i < slice_size:
            local_sum += my_vector[i]
            i+=1

        print("task",rank,"sum:",local_sum)

        global_sum = comm.allreduce(local_sum, MPI.SUM)
        global_mean = global_sum/SIZE

        local_sum_sq_diff = 0
        n = 0
        while n < slice_size:
            temp = (my_vector[n] - global_mean)**2
            local_sum_sq_diff += temp
            n+=1

        global_sum_of_sq_diff = comm.reduce(local_sum_sq_diff,MPI.SUM)

        if rank == 0:
            sd = math.sqrt(global_sum_of_sq_diff/SIZE)
            print("Standard Deviation:",sd)
    else:
        if(rank == 0):
            print("Vector size is not evenly divisble by the number of processors. Please try again.")


if __name__ == "__main__":
    main(sys.argv[1:])
