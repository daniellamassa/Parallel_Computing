from mpi4py import MPI

#TO RUN: mpiexec -n 4 python3 MPI_array_sum.py
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

bigArray = [3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2,3,0,7,8,1,6,4,0,6,2,8,6,2,0,8,9,9,8,6,2,8,0,3,4,8,2,5,3,4,2,1,1,7,0,6,7,9,8,2,1,4,8,0,8,6,5,1,3,2,8,2,3,0,6,6,4,7,0,9,3,8,4,4,6,0,9,5,5,0,5,8,2,2,3,1,7,2,5,3,5,9,4,0,8,1,2,8,4,8,1,1,1,7,4,5,0,2,8,4,1,0,2,7,0,1,9,3,8,5,2,1,1,0,5,5,5,9,6,4,4,6,2,2,9,4,8,9,5,4,9,3,0,3,8,1,9,6,4,4,2,8,8,1,0,9,7,5,6,6,5,9,3,3,4,4,6,1,2,8,4,7,5,6,4,8,2,3,3,7]

localsum = 0
globalsum = 0

quotient = len(bigArray)//size
remainder = len(bigArray)%size

if rank < remainder:
    block_size = quotient+1
    start_index = rank * block_size
else:
    block_size = quotient
    start_index = rank * block_size + remainder

end_index = start_index + block_size

i = start_index

while i < end_index:
    localsum += bigArray[i]
    i+=1

print("local sum of process ",rank," is: ",localsum)

if rank != 0:
    comm.send(localsum, dest=0, tag=rank)
else:
    globalsum = localsum
    q = 1
    while q < size:
        globalsum += comm.recv(source=q, tag=MPI.ANY_TAG)
        q+=1

    print("The total sum is: ",globalsum)
