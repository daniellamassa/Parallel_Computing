
<center>Dani Massa</center>

# Assignment 1: C Bootcamp

Timing for Assignment 1 Step 3:
- Large Prime Number 5915587277: 40962.809000 ms
- Large Non-Prime Number 2568963242: 17422.581000 ms
- Small Prime Number 89: 0.037000 ms 
- Small Non-Prime Number 100: 0.058000 ms

Timing for Assignment 1 Step 4:
- Small Square Root Number 49: 0.049000 ms
- Large Square Root Number 996004: 4.531000 ms

Why might you get get different time values for the same number?

Different time values for the same number may occur due to the fact that the computer may be running multiple processes at the same time. To be more specific, the variation in time is not very significantly different, but a little variation is to be expected due to the computer completing other tasks in the background.

What happens if you mess up the vector size argument and make it bigger than the actual size of the vector? 

For this question, what essentially is happening is that the code is indexing out of range. However, C still lets you compile and run code even if this occurs. Instead of producing an error, the output of the code is slightly modified. To be more specific, if the vector size argument is bigger than the actual size of the vector, the code generates the two vectors according to the larger size. However, once the code reaches the point where is at an index out of range (i.e. there are no more values left to put into the vector), it just produces a series of null floating point values (0.0000...) to fill the empty space. 

Timing for Assignment 2 Step 7:
- Vector Size 10: 0.071000 ms
- Vector Size 500:  0.540000 ms
- Vector Size 20000: 11.365000 ms
- Vector Size: 500000: 256.230000 ms
- Vector Size: 5000000000 (size got automatically set to 705032704): 401678.202000

How big can you make them?
- approx. ~ 705032704
Does the code ever get slow?
- Yes! As the size of the vectors increase, the speed of the code decreases. 

