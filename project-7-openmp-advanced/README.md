# <center>Project 8: OpenMP Advanced</center>

* Note: use "gcc filename.c -lm -fopenmp" to compile, could not get Makefile to work.
* Note: numbers in parenthesis with static/dynamic represent the chunk size.

# <center>Part 1: Serial Function Timing</center>

|             | 100x        | 500x        | 1000x       | 2000x       | 4000x       | 8000x       |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| addition    | 0.000118 s  | 0.001350 s  | 0.005268 s  | 0.020377 s  | 0.081126 s  | 0.324164 s  |
|transposition| 0.000128 s  | 0.001759 s  | 0.006681 s  | 0.031294 s  | 0.151303 s  | 0.872490 s  |

* Note: These timings were taken only of the functions; print statements were excluded.

# <center>Part 2.1: Parallel Matrix Operation: Addition </center>
* SIZE: 100x

| threads     | static (1)  | static (10) | static (100)|dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| 1           | 0.001158 s  | 0.000220 s  | 0.000124 s  | 0.001336 s  | 0.000220 s  | 0.000124 s  |
| 2           | 0.000923 s  | 0.000056 s  | 0.000045 s  | 0.000903 s  | 0.000041 s  | 0.000045 s  |
| 3           | 0.000463 s  | 0.000047 s  | 0.000015 s  | 0.000433 s  | 0.000057 s  | 0.000028 s  |
| 4           | 0.000277 s  | 0.000029 s  | 0.000010 s  | 0.000281 s  | 0.000031 s  | 0.000013 s  |

* SIZE: 500x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.007525 s  | 0.001387 s  | 0.000815 s  || 0.007627 s  | 0.001348 s  | 0.000790 s  |
| 2           | 0.009894 s  | 0.001086 s  | 0.000480 s  || 0.010478 s  | 0.001123 s  | 0.000521 s  |
| 3           | 0.008337 s  | 0.001067 s  | 0.000393 s  || 0.008158 s  | 0.001048 s  | 0.000386 s  |
| 4           | 0.006553 s  | 0.000794 s  | 0.000277 s  || 0.006604 s  | 0.000798 s  | 0.000271 s  |

* SIZE: 1000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.031195 s  | 0.005498 s  | 0.003403 s  || 0.031050 s  | 0.005543 s  | 0.003321 s  |
| 2           | 0.038843 s  | 0.004477 s  | 0.001989 s  || 0.041350 s  | 0.004526 s  | 0.002004 s  |
| 3           | 0.036981 s  | 0.004770 s  | 0.001848 s  || 0.037652 s  | 0.004808 s  | 0.002014 s  |
| 4           | 0.027628 s  | 0.003687 s  | 0.001714 s  || 0.026480 s  | 0.003853 s  | 0.001663 s  |

* SIZE: 2000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.039928 s  | 0.015464 s  | 0.012560 s  || 0.123842 s  | 0.022067 s  | 0.012880 s  |
| 2           | 0.016012 s  | 0.008856 s  | 0.007381 s  || 0.167875 s  | 0.018188 s  | 0.002004 s  |
| 3           | 0.023075 s  | 0.018346 s  | 0.013319 s  || 0.145508 s  | 0.018770 s  | 0.007999 s  |
| 4           | 0.016132 s  | 0.016132 s  | 0.009665 s  || 0.107471 s  | 0.014832 s  | 0.006442 s  |

* SIZE: 4000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.153698 s  | 0.061861 s  | 0.048064 s  || 0.478667 s  | 0.085835 s  | 0.049616 s  |
| 2           | 0.062473 s  | 0.034543 s  | 0.029116 s  || 0.642225 s  | 0.069770 s  | 0.031588 s  |
| 3           | 0.044546 s  | 0.028318 s  | 0.023758 s  || 0.514044 s  | 0.068029 s  | 0.026495 s  |
| 4           | 0.041226 s  | 0.025783 s  | 0.021490 s  || 0.408843 s  | 0.053107 s  | 0.021548 s  |

* SIZE: 8000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.636992 s  | 0.249022 s  | 0.203344 s  || 1.979174 s  | 0.354729 s  | 0.203552 s  |
| 2           | 0.256270 s  | 0.142511 s  | 0.120167 s  || 2.548387 s  | 0.284012 s  | 0.128335 s  |
| 3           | 0.351453 s  | 0.279540 s  | 0.208275 s  || 2.302932 s  | 0.300060 s  | 0.117895 s  |
| 4           | 0.353684 s  | 0.288856 s  | 0.162565 s  || 1.724344 s  | 0.236196 s  | 0.106910 s  |

# <center>Part 2.2: Parallel Matrix Operation: Transposition </center>
* SIZE: 100x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.000084 s  | 0.000045 s  | 0.000038 s  || 0.000626 s  | 0.000062 s  | 0.000027 s  |
| 2           | 0.000117 s  | 0.000017 s  | 0.000014 s  || 0.000402 s  | 0.000054 s  | 0.000114 s  |
| 3           | 0.000043 s  | 0.000012 s  | 0.000010 s  || 0.006811 s  | 0.000161 s  | 0.000017 s  |
| 4           | 0.000053 s  | 0.000024 s  | 0.000020 s  || 0.015683 s  | 0.009280 s  | 0.000009 s  |

* SIZE: 500x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.003126 s  | 0.001158 s  | 0.000810 s  || 0.019687 s  | 0.003796 s  | 0.002209 s  |
| 2           | 0.000994 s  | 0.000466 s  | 0.000434 s  || 0.009079 s  | 0.001329 s  | 0.000602 s  |
| 3           | 0.000632 s  | 0.000346 s  | 0.000281 s  || 0.009145 s  | 0.001200 s  | 0.000818 s  |
| 4           | 0.014353 s  | 0.000614 s  | 0.000536 s  || 0.006911 s  | 0.001031 s  | 0.000336 s  |

* SIZE: 1000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.010931 s  | 0.004711 s  | 0.004341 s  || 0.038644 s  | 0.007333 s  | 0.004341 s  |
| 2           | 0.003942 s  | 0.002241 s  | 0.001971 s  || 0.043304 s  | 0.005228 s  | 0.002466 s  |
| 3           | 0.003219 s  | 0.001891 s  | 0.001662 s  || 0.039806 s  | 0.005258 s  | 0.002128 s  |
| 4           | 0.009425 s  | 0.002265 s  | 0.005597 s  || 0.030956 s  | 0.004261 s  | 0.001823 s  |

* SIZE: 2000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.046183 s  | 0.022637 s  | 0.021602 s  || 0.179873 s  | 0.036098 s  | 0.022828 s  |
| 2           | 0.035911 s  | 0.021073 s  | 0.018026 s  || 0.169746 s  | 0.028231 s  | 0.015134 s  |
| 3           | 0.019500 s  | 0.019522 s  | 0.020605 s  || 0.158463 s  | 0.021327 s  | 0.009749 s  |
| 4           | 0.013901 s  | 0.013047 s  | 0.008935 s  || 0.126114 s  | 0.018237 s  | 0.007773 s  |

* SIZE: 4000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 0.214066 s  | 0.121889 s  | 0.116470 s  || 0.822716 s  | 0.188670 s  | 0.126071 s  |
| 2           | 0.180576 s  | 0.109694 s  | 0.098509 s  || 0.776698 s  | 0.111791 s  | 0.056707 s  |
| 3           | 0.184888 s  | 0.113190 s  | 0.097886 s  || 0.678913 s  | 0.099155 s  | 0.047082 s  |
| 4           | 0.090954 s  | 0.048584 s  | 0.040543 s  || 0.559651 s  | 0.086227 s  | 0.039242 s  |

* SIZE: 8000x

| threads     | static (1)  | static (10) | static (100)||dynamic (1)  |dynamic (10) |dynamic (100)|
| ----------- | ----------- | ----------- | ----------- || ----------- | ----------- | ----------- |
| 1           | 1.285190 s  | 0.705832 s  | 0.699623 s  || 4.074450 s  | 1.015368 s  | 0.728763 s  |
| 2           | 0.670335 s  | 0.321940 s  | 0.282182 s  || 3.481957 s  | 0.661650 s  | 0.392584 s  |
| 3           | 1.062138 s  | 0.677042 s  | 0.626662 s  || 3.205392 s  | 0.591409 s  | 0.317028 s  |
| 4           | 0.672598 s  | 0.306947 s  | 0.240556 s  || 2.737129 s  | 0.481549 s  | 0.275234 s  |

# <center> Analysis</center>
* For the majority of these test cases, speedup effects did occur. This can be seen when viewing the data across a row or down a column: the elapsed time tends to decrease as thread and chunk size increases.
* However, there are certain cases in which the speedup effects are less straightforward in the sense that they did not scale linearly. This may have occurred due to cache incoherence and false sharing. More specifically, this has to do with how shared resources are modified within and between caches correctly. For false sharing, if two threads with separate caches are referencing a variable on the same cache line, and one of those threads tries to update the variable, then the program is forced to look into main memory in order to assure that both thread's caches have the new updated variable.  
* Additionally, I originally expected that cases within the dynamic scheduling condition would take less time than those in the static scheduling condition. I thought this would occur because with dynamic scheduling, once a thread finishes a chunk, it has the ability to request more (which results in little to no wait time/stalling of threads). However, I soon realized that dynamic scheduling has more overhead than static scheduling. This is likely the reason why static scheduling had smaller elapsed times per condition than dynamic scheduling.
