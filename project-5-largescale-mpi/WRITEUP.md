# Project - 5 : Large Scale MPI

#### Daniella Massa 23'
#### Leonardo Ferrisi 23'

# TIC TAC TOE, Parallelized

We embarked on this project initially intending to have a parallel and scalable TIC, TAC, TOE game.

This involved redefining the board as a 2-dimensional array of all the rows in the board, as well as
tweaking the code dictating where pieces are placed and parallelizing the code that checks for winning states - as instead of being
hard-coded, the new win checker had to be able to dynamically check for rows and diagonals for win states.

The code for a scalable Tic Tac Toe game can be found in '''ttt-scale.c'''

Unfortunately, there was a bug in the scalable code we never figured how to fix involving parallelizing minimax.
In principle, just have a minimax run per node check its subset of board states then get the max of board states possible across all nodes.
However, for whatever reason, the computer never registered where it put its piece and always placed a piece in the same spot.
This was likely due to some issue in how we broadcasted the board state after the computer makes a move. However we weren't able to find a solution.

# ------------------------

The computer move code however, was much easier to parallelize for the hardcoded 9-square board. 

See '''ttt-computer.c''' and '''ttt.parallel.c''' for more info.

'''ttt-computer.c''' plays the computer against itself

'''ttt-parallel''' is the standard format where we play against a computer

*Timings were done for '''ttt-parallel.c''' where timing only measures the computer thinking time.*
**** *the program does tell you how long you took to make moves though*

#### Some Timings for ttt-computer.c

###### *Where we measured all the time taken by both the player and computer move*

| Num_Proc    | player moves first | Speedups |
| ----------- | ----------------- | ---------------|
| p = 1       | 23.856000 ms      | Baseline|
| p = 2       | 22.634000 ms      | 1.05 or 5% |
| p = 3       | n%p != 0          |  NA  |
| p = 4       | 22.856000 ms      | 0.99 or -1%|

| Num_Proc    |  CPU moves first | Speedups |
| ----------- | ----------------- | ---------------|
| p = 1       |  23.151000 ms|   Baseline           |
| p = 2       |  21.310000 ms|   1.09 or 9%          |
| p = 3       |  n%p != 0    |    NA           |
| p = 4       |  22.095000 ms|   0.96 or -4%             |


#### Some Timings for ttt-parallel.c

###### *Where we measured just the time for computer move*

| Num_Proc    |  player moves first | Speedups |
| ----------- | ----------------- | ---------------|
| p = 1       |  9.023507 ms|   Baseline           |
| p = 2       |  2.581043 ms|   3.496 or 247%%          |
| p = 3       |  1.911785 ms    |   1.35 or 35%            |
| p = 4       |  1.607975 ms|   1.18 or 18%            |

| Num_Proc    |  CPU moves first | Speedups |
| ----------- | ----------------- | ---------------|
| p = 1       |  51.676420 ms|   Baseline           |
| p = 2       |  24.679604 ms|   2.09 or 109%          |
| p = 3       |  15.748786 ms    |  1.57 or 57%          |
| p = 4       |  17.499424 ms|   0.90 or -10%             |

### Contributions

##### Leonardo: 
- Scaling the Tic Tac Toe board
    - Parallelizing win functions for dynamically allocated tic tac toe arrays of varying sizes
- Timing code for Computer v player game such that only computer time can be measured if need be
- Debugging

##### Dani:
- Scaling and Parallelizing Computer move
- Making the Computer vs Computer file
- Timing
- Debugging 
