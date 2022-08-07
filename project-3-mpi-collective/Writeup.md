# <center> Week 3 Assignments</center>

# <center> Part 1: Vector Normalization</center>

|             | n = 100     | n = 1000    | n = 10000   |
| ----------- | ----------- | ----------- | ----------- |
| p = 1       | 25.257000 ms| 23.758000 ms| 24.090000 ms|
| p = 2       | 21.775000 ms| 23.000000 ms| 23.454000 ms|
| p = 3       | n%p != 0    | n%p != 0    | n%p != 0    |
| p = 4       | 22.137000 ms| 24.765000 ms| 21.765000 ms|

* There does not appear to be any significant or consistent speedup effects for vector normalization.<br>

Notes:
* I was able to successfully implement the given parallelized vector normalization algorithm into my code. I also ensured that my code was correct by having it print the magnitude of the normalized vector (which should be 1). I tested this on a variety of vector sizes and number of processors.
* In order to compile this code, the -lm flag needs to be added at the end of the command line call, for example: "mpicc -std=c99 -Wall MPI_Normalize_Vector.c -o vector_norm -lm"
* The size of the vector is taken as a command line argument.
* I used the exit function when detecting whether or not n%p == 0. However, I also saw that an MPI_Abort() function exists as well, but I had trouble implementing it.

# <center> Part 2: Even Odd Transposition Sort</center>

|             | n = 100     | n = 1000    | n = 10000   |
| ----------- | ----------- | ----------- | ----------- |
| p = 1       | 22.933000 ms| 29.696000 ms| 27.977000 ms|
| p = 2       | 21.698000 ms| 23.893000 ms| 23.994000 ms|
| p = 3       | 24.027000 ms| 22.169000 ms| 27.162000 ms|
| p = 4       | 23.128000 ms| 30.915000 ms| 23.785000 ms|

* There does not appear to be any significant or consistent speedup effects for even odd transposition sort.<br>
