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
        #use random.random() for decimals between 0-1..
        index +=1
    return vector

def main(argv):
    comm = MPI.COMM_WORLD
    processors = comm.Get_size()
    rank = comm.Get_rank()

    SIZE = int(sys.argv[1])
    vector1 = []
    vector2 = []
    # TEST CASES
    #vector1 = [2.130386, 0.980787, 4.614736, 0.436358, 0.501426, 0.759134, 0.710526, 1.039331, 0.886260, 0.233295]
    #vector2 = [0.067112, 0.170649, 0.390775, 1.192830, 4.576829, 0.611280, 2.069508, 1.216036, 0.507397, 0.379223]
    local_result = 0.0
    global_result = 0.0

    if rank == 0:
        vector1 = randomize_vector(vector1, SIZE)
        vector2 = randomize_vector(vector2, SIZE)
        #print_vector(vector1, SIZE)
        #print_vector(vector2, SIZE)
        i = 1
        while i < processors:
            comm.send(vector1, dest=i, tag=1)
            comm.send(vector2, dest=i, tag=2)
            i+=1
    else:
        vector1 = comm.recv(source=0, tag=1)
        vector2 = comm.recv(source=0, tag=2)
        #print_vector(vector1, SIZE)
        #print_vector(vector2, SIZE)

    #calculate the partial solution of vector dot product on all tasks
    n = rank
    while n < SIZE:
        local_result += vector1[n] * vector2[n]
        n += processors
    print("local vector dot product of process",rank,"is",local_result)

    if rank != 0:
        comm.send(local_result, dest=0, tag=rank)
    else:
        global_result = local_result
        q = 1
        while q < processors:
            global_result += comm.recv(source=q, tag=MPI.ANY_TAG)
            q+=1

        print("Vector Dot Product:",global_result)
        # Test Case: vector dot product is is 8.665609

if __name__ == "__main__":
    main(sys.argv[1:])
