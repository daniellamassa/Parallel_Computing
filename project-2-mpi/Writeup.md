# <center>Week 2 Assignments</center>

# <center> Part 1: Array Sum</center>

In order to modify the code so that it distributes the data block wise rather than cyclically, I implemented the algorithm from the textbook that we discussed in class. This consisted of 5 new variables: quotient, remainder, block_size, start_index, and end_index. The quotient represents the number of items in the array divided by the number of processors. The remainder accounts for the amount of leftover items (such that the number of items in the array is not evenly divisible by the number of processors). I then added an if-else statement, in which the "else" section accounts for n%p == 0. If this is the case, the block size is equivalent to the quotient. The "if" sections accounts for n%p != 0. If this is the case, the block size is equal to the quotient + 1, for all processor ranks that are less than the remainder. The start and end indices are assigned accordingly (each processor has a different start and end index). Finally, I had to slightly modify the for loop so that functioned based off of the start and end indices of each processor.

# <center> Part 2: Vectorized Vector Operations</center>

|             | n = 100     | n = 1000    | n = 10000   |
| ----------- | ----------- | ----------- | ----------- |
| p = 1       | 34.927000 ms| 32.734000 ms| 36.381000 ms|
| p = 2       | 33.515000 ms| 33.949000 ms| 34.733000 ms|
| p = 3       | 28.274000 ms| 33.851000 ms| 27.605000 ms|
| p = 4       | 23.894000 ms| 30.012000 ms| 24.927000 ms|


* There appears to be some significant speedup effects. An 100 item array ran 11 seconds faster on 4 processors compared to 1 processor. An 1000 item array ran 2-3 seconds faster on 4 processors compared to 1 processor. An 10000 item array ran 10-11 seconds faster on 4 processors compared to 1 processor.

# <center> Important Notes</center>


* The size of the array for part 2 is given as a command line argument, such that the formatting is as follows: <br>
mpirun -np 4 ./executable_name 10 <br>
In which 10 represents the size of the array, and 4 represents the number of processors.
* The school computers have a issue with using drand48() along with MPI. Attempting to use drand48() resulted in an implicit function call (even though the proper import statements were used). I am under the impression that this is an issue specific to MPI because my code from week_1_bootcamp vectors.c runs perfectly fine on the school computers (it uses drand48(), but no MPI stuff). Additionally, the "-std=c99" tag in the command line call to compile the code did not resolve this issue. I personally "fixed" this bug by using the rand() function instead, and then casting a divided value to a double (not the most eloquent solution, I know). This bug was also mentioned in the Slack channel.
