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

def scatter(vector, SIZE, processors, rank):
    #slice_size = SIZE//processors
    my_slice = []

    quotient = SIZE//processors
    remainder = SIZE%processors

    if rank < remainder:
        block_size = quotient+1
        start_index = rank * block_size
    else:
        block_size = quotient
        start_index = rank * block_size + remainder

    end_index = start_index + block_size

    i = start_index
    print(i,",",end_index)
    while i <= end_index:
        num = vector[i]
        my_slice.append(num)
        i+= 1

    return my_slice

def main(argv):
    comm = MPI.COMM_WORLD
    processors = comm.Get_size()
    rank = comm.Get_rank()

    SIZE = int(sys.argv[1])
    slice_size = SIZE//processors
    original_vector = []
    result_vector = []
    slice = []
    local_sum = 0
    magnitude = 0
    chunks = []

    if SIZE%processors == 0:
        if (rank == 0):
            original_vector = randomize_vector(original_vector,SIZE)
            # cyclic distribution of data
            chunks = [[] for _ in range(processors)]
            for i, chunk in enumerate(original_vector):
                chunks[i % processors].append(chunk)
            print_vector(original_vector,SIZE)
            #print(chunks)

    else:
        if(rank == 0):
            print("Vector size is not evenly divisble by the number of processors. Please try again.")

    slice = comm.scatter(chunks,0)
    #print_vector(slice,slice_size)
    i = 0
    while i < slice_size:
        local_sum += slice[i] * slice[i]
        i+=1
    if rank != 0:
        comm.send(local_sum, dest=0, tag=rank)
    else:
        other_sum = 0
        q = 1
        while q < processors:
            other_sum += comm.recv(source=q, tag=MPI.ANY_TAG)
            local_sum += other_sum
            q+= 1

        magnitude = math.sqrt(local_sum)

        magnitude = comm.bcast(magnitude, root=0)
        z = 0
        while z < slice_size:
            slice[z] = slice[z]/magnitude
            z+=1
    result_vector = comm.gather(chunks,root=0)
    print(result_vector)

    print(result_vector)
    if rank ==0:
        test_case_mag = 0
        test_case_sum = 0
        p = 0
        while p < SIZE:
            test_case_sum += result_vector[p] * result_vector[p]
            p+=1
        test_case_mag = math.sqrt(test_case_sum)
        #print(test_case_mag)




































if __name__ == "__main__":
    main(sys.argv[1:])
