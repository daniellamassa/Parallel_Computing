## Final Project Writeup

* Dani Massa


I was able to successfully implement python MPI with several vector operations. Those of which included: vector dot products, vector means, vector standard deviation, and vector sums. I utilized several online resources to comprehend the documentation for python MPI. Something new I learned that I found interesting was that there are several ways to implement python4mpi. For example, functions such as comm.send() and comm.recv() can be used on their own to send a python object, or NumPy arrays can be implemented to speed up this process. When I started this project I did not utilize the feature of NumPy arrays, and looking back I believe that importing this module would have improved my project.

Another interesting thing I found out is how scatter() and gather() work with python. As I was working through this project, I soon found out that scatter() in python is very different from scatter() in C++. The main difference is that the scatter function in python expects the size of the data to be scattered to be equivalent to the number of processors. For example, if we ran a program that scatters an array over 4 processors, the array would have to be of size 4. If we wanted to have an array of size 20 (to send sub-arrays of 5 items to 4 processors), scatter would not work. I had to manually split up the sub-arrays within my code before calling scatter, which also impacted how gather() was implemented.

Overall, I completed project 2 (mpi) and project 4 (advanced mpi) utilizing the python4mpi library (functions included: send, recv, broadcast, reduce, and allreduce).I had trouble implementing project 3 due to the previously mentioned issues with collective communication in python MPI. However, I was able to design code that manually separated a big array into sub-arrays to be scattered (both cyclically and block-wise). However this generated bugs when trying to gather those sub-arrays back into a single big array. I ran into these issues when trying to implement vector normalization, and even-odd transposition sort.

Speedups: my python implementation of MPI was significantly slower than my C++ implementation of MPI. I believe this could be resolved by using numpy arrays with message passing.
