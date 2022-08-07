# <center> Week 3 Assignments</center>

# <center> Part 1: Vector Mean</center>

|             | n = 100     | n = 1000    | n = 10000   | n = 100000  | n = 1000000 |n = 10000000 |n = 100000000|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| p = 1       | 23.856000 ms| 23.151000 ms| 23.393000 ms| 28.808000 ms| 65.790000 ms|232.945000 ms|2261.723000 ms|
| p = 2       | 22.634000 ms| 21.310000 ms| 17.806000 ms| 24.003000 ms| 53.127000 ms|140.385000 ms|970.273000 ms|
| p = 3       | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    |
| p = 4       | 22.856000 ms| 22.095000 ms| 22.604000 ms| 25.573000 ms| 31.249000 ms| 83.864000 ms|511.461000 ms|

* For vector mean, there appears to be significant and consistent speedup effects for vector sizes of 1000000 and above (the last three columns).

# <center> Part 2: Vector STD</center>

|             | n = 100     | n = 1000    | n = 10000   | n = 100000  | n = 1000000 |n = 10000000 |n = 100000000|
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| p = 1       | 26.417000 ms| 23.994000 ms| 25.661000 ms| 29.188998 ms|100.658000 ms|589.411000 ms|5150.927000 ms|
| p = 2       | 22.096000 ms| 23.373000 ms| 22.557000 ms| 29.535000 ms| 73.040000 ms|302.795000 ms|2653.738000 ms|
| p = 3       | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    | n%p != 0    |
| p = 4       | 22.366000 ms| 22.982000 ms| 30.404000 ms| 28.007000 ms| 41.310000 ms|169.060000 ms|1355.638000 ms|

* For vector standard deviation, there appears to be significant and consistent speedup effects for vector sizes of 1000000 and above (the last three columns).
