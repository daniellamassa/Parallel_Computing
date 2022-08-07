# <center>Project 7: OpenMP</center>

* Note: Part 1 (No Sugar Array Sum) was skipped; I was notified via slack that submission for part 1 was not required.
* Note: use "gcc filename.c -lm -fopenmp" to compile, could not get Makefile to work.

# <center>Part 2: Vector Operations</center>

# <center>Part 2.1: Vector Addition</center>
|             | n = 100     | n = 1000    | n = 10000   | n = 100000  | n = 1000000 |n = 10000000 |n = 100000000|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| t = 1       | 0.000011 ms | 0.000020 ms | 0.000104 ms | 0.000470 ms | 0.005045 ms | 0.047050 ms | 0.464271 ms |
| t = 2       | 0.000166 ms | 0.000175 ms | 0.000235 ms | 0.000318 ms | 0.002604 ms | 0.024796 ms | 0.244551 ms |
| t = 3       | 0.000221 ms | 0.000216 ms | 0.000264 ms | 0.000243 ms | 0.001822 ms | 0.017080 ms | 0.168241 ms |
| t = 4       | 0.002491 ms | 0.000261 ms | 0.001954 ms | 0.000234 ms | 0.001515 ms | 0.013554 ms | 0.132818 ms |

# <center>Part 2.2: Vector Mean</center>
|             | n = 100     | n = 1000    | n = 10000   | n = 100000  | n = 1000000 |n = 10000000 |n = 100000000|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| t = 1       | 0.000010 ms | 0.000021 ms | 0.000109 ms | 0.000242 ms | 0.002579 ms | 0.025780 ms | 0.259992 ms |
| t = 2       | 0.000109 ms | 0.000168 ms | 0.000232 ms | 0.000193 ms | 0.001359 ms | 0.012889 ms | 0.127872 ms |
| t = 3       | 0.000219 ms | 0.000229 ms | 0.000276 ms | 0.000169 ms | 0.000953 ms | 0.008760 ms | 0.085942 ms |
| t = 4       | 0.003033 ms | 0.000319 ms | 0.002297 ms | 0.000164 ms | 0.000807 ms | 0.006720 ms | 0.067328 ms |

# <center>Part 2.3: Vector Magnitude</center>
|             | n = 100     | n = 1000    | n = 10000   | n = 100000  | n = 1000000 |n = 10000000 |n = 100000000|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| t = 1       | 0.000010 ms | 0.000022 ms | 0.000110 ms | 0.000248 ms | 0.002613 ms | 0.025608 ms | 0.256809 ms |
| t = 2       | 0.000161 ms | 0.000162 ms | 0.000217 ms | 0.000191 ms | 0.001408 ms | 0.013305 ms | 0.129681 ms |
| t = 3       | 0.000214 ms | 0.000231 ms | 0.000226 ms | 0.000163 ms | 0.001010 ms | 0.008754 ms | 0.088554 ms |
| t = 4       | 0.000244 ms | 0.000266 ms | 0.000296 ms | 0.000161 ms | 0.000815 ms | 0.006815 ms | 0.067874 ms |

# <center>Part 2.5: Vector Normalization</center>
|             | n = 100     | n = 1000    | n = 10000   | n = 100000  | n = 1000000 |n = 10000000 |n = 100000000|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| t = 1       | 0.000014 ms | 0.000030 ms | 0.000196 ms | 0.000454 ms | 0.004744 ms | 0.047165 ms | 0.469970 ms |
| t = 2       | 0.000149 ms | 0.000164 ms | 0.000260 ms | 0.000308 ms | 0.002462 ms | 0.024144 ms | 0.242836 ms |
| t = 3       | 0.000215 ms | 0.000221 ms | 0.000283 ms | 0.000243 ms | 0.002264 ms | 0.017964 ms | 0.180768 ms |
| t = 4       | 0.000227 ms | 0.000304 ms | 0.000320 ms | 0.000215 ms | 0.001527 ms | 0.015694 ms | 0.156679 ms |


# <center>Part 3: Numerical Integration Estimation of Pi</center>
|             | n = 100     | n = 1000    | n = 10000   | n = 100000  | n = 1000000 |n = 10000000 |n = 100000000|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| t = 1       | 0.000013 ms | 0.000048 ms | 0.000399 ms | 0.002900 ms | 0.010548 ms | 0.085206 ms | 0.828611 ms |
| t = 2       | 0.000150 ms | 0.000181 ms | 0.000365 ms | 0.002079 ms | 0.006172 ms | 0.044683 ms | 0.426811 ms |
| t = 3       | 0.000182 ms | 0.000223 ms | 0.000333 ms | 0.001394 ms | 0.005088 ms | 0.030505 ms | 0.286625 ms |
| t = 4       | 0.000236 ms | 0.000267 ms | 0.000327 ms | 0.001098 ms | 0.004101 ms | 0.026200 ms | 0.221257 ms |

* Speedup affects can be seen by reading down each column.  
* For smaller problem sizes in the first three columns (n = 100, n = 1000, and n = 10000), there were no significant speedup effects.
* For larger problem sizes in the last four columns (n = 100000, n = 1000000, n = 10000000, and n = 100000000), significant speedup effects did occur. For a given problem size, as the number of threads increased, the total time elapsed decreases.
* Speedup effects were not shown in the first three columns because the problem size was too small to produce significant speedup results. In other words, the computer ran through these problem sizes incredibly quickly, therefore no speedup occurred.
* Speedup effects were shown in the last four columns because the problem size was large enough to produce significant speedup results. In other words, with more threads working on a large problem size, the program was able to efficiently split up the work between threads, which resulted in shorter run times.    
