// Tic-tac-toe playing AI. Exhaustive tree-search. WTFPL
// adapted from
// Matthew Steel 2009, www.www.repsilat.com

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> //for random seed
#include <math.h> //need to compile with -m
// to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
// to run (simple): mpirun ./MPI_blank

#define DEFAULT_BOARDSIZE 9
#define DEFAULT_SIDELEN 3

char gridChar(int i)
{
    switch (i)
    {
    case -1:
        return 'X';
    case 0:
        return ' ';
    case 1:
        return 'O';
    default:
        printf("If you are in this case you done fucked up\n");
        exit(1);
    }
}

void draw(int sidelen, int (*board)[sidelen])
{
    for (int i = 0; i < sidelen; i++)
    {
        for (int j = 0; j < sidelen; j++)
        {
            if (j == sidelen - 1)
            {
                printf(" %c \n", gridChar(board[i][j]));
                if (i != sidelen - 1)
                {
                    // print a bar underneath
                    for (int k = 0; k < sidelen - 1; k++)
                    {
                        printf("---+");
                    }
                    printf("---\n");
                }
            }
            else
            {
                printf(" %c |", gridChar(board[i][j]));
            }
        }
    }
}

int *convertCoords(int oneDCoord, int sidelen)
{
    int *toReturn = malloc(sizeof(int) * 2);
    if (oneDCoord < sidelen)
    {
        toReturn[0] = 0;
        toReturn[1] = oneDCoord;
    }
    else
    {
        int row = oneDCoord / sidelen;
        toReturn[0] = row;
        toReturn[1] = oneDCoord % sidelen;
    }
    return toReturn;
}

int wStraight(int sidelen, int (*board)[sidelen], int my_rank, int comm_sz)
{
    // row checking
    for (int row = my_rank; row < sidelen; row += comm_sz)
    {
        bool rWin = true;
        int curX = board[row][0];

        for (int pos = 1; pos < sidelen; pos++)
        {
            int nextX = board[row][pos];

            if (curX != nextX || nextX == 0 || curX == 0)
            {
                rWin = false;
                break;
            }
        }
        if (rWin == true)
        {
            printf("win found at task %d at row: %d\n", my_rank, row);
            return curX;
        }
    }

    // column checking
    for (int col = my_rank; col < sidelen; col += comm_sz)
    {
        bool cWin = true;
        int curX = board[0][col];

        for (int pos = 1; pos < sidelen; pos++)
        {
            int nextX = board[pos][col];

            if (curX != nextX || nextX == 0 || curX == 0)
            {
                cWin = false;
                break;
            }
        }
        if (cWin == true)
        {
            printf("win found at task %d at column: %d\n", my_rank, col);
            return curX;
        }
    }
    return 0;
}

int wD(int sidelen, int (*board)[sidelen])
{
    int iF = board[0][0];
    int iB = board[0][sidelen - 1];

    for (int i = 0; i < sidelen; i++)
    {
        if (iF != 0)
        { // getting "\" diagonal
            if (iF == board[i][i])
            {
                iF = board[i][i];
            }
            else
            {
                iF = 0;
            }
        }

        if (iB != 0)
        { // getting "/" diagonal
            if (iB == board[i][(sidelen - 1) - i])
            {
                iB = board[i][(sidelen - 1) - i];
            }
            else
            {
                iB = 0;
            }
        }
    }

    if (iF != 0 && iB == 0)
    {
        return iF;
    }
    else if (iF == 0 && iB != 0)
    {
        return iB;
    }
    else
    {
        return 0;
    }
}

int win(int sidelen, int (*board)[sidelen], int my_rank, int comm_sz)
{
    // check if board size is legal
    if (sidelen % 2 == 0)
    {
        printf("\n[Error] Side Length cannot be even\n");
        exit(1);
    }

    int horz = wStraight(sidelen, board, my_rank, comm_sz);
    int diag = wD(sidelen, board);

    if (diag != 0 && horz == 0)
    {
        return diag;
    }
    else if (diag == 0 && horz != 0)
    {
        return horz;
    }
    else
    {
        return 0; // Default return value
    }
}

// minimax in a single recursive function
//  you call max if it is your move
//  and min if it is your opponent's move.

// Can only run on root node
int minimax(int sidelen, int (*board)[sidelen], int player, int winState, int my_rank, int comm_sz)
{
    // How is the position like for player (their turn) on board?
    int winner = winState;
    if (winner != 0)
        return winner * player; // base case

    int curbestmove = -1;  // the best move possible
    int curbestscore = -2; // Losing moves are preferred to no move
    int i;
    int boardSize = sidelen * sidelen;
    int coords[2] = {0};
    for (i = 0; i < boardSize; ++i)
    { // For all moves,
        coords[0] = convertCoords(i, sidelen)[0];
        coords[1] = convertCoords(i, sidelen)[1];
        if (board[coords[0]][coords[1]] == 0)
        {                                         // If legal,
            board[coords[0]][coords[1]] = player; // Try the move
            //    draw(board);
            //	    getchar();
            int currentWinstate = win(sidelen, board, my_rank, comm_sz);
            int thisScore = -1 * minimax(sidelen, board, player * -1, currentWinstate, my_rank, comm_sz);
            if (thisScore > curbestscore)
            {
                curbestscore = thisScore;
                curbestmove = i;
            }                                // Pick the one that's worst for the opponent
            board[coords[0]][coords[1]] = 0; // Reset board after try
        }
    }
    if (curbestmove == -1)
        return 0;
    return curbestscore;
}

// Should run on every node... however, all minimax should only ever be done in the root node
void computerMove(int sidelen, int (*board)[sidelen], int my_rank, int comm_sz)
{
    int boardSize = sidelen * sidelen;
    int move = -1;
    // int *twoDmove = convertCoords(move, sidelen);
    int score = -2;
    int i;
    int finalBest;

    // SUGGESTED REWRITE, we need to distribute possbile moves out of boardsize to each node
    // EXAMPLE: 0 gets moves 0-2, 1 gets moves 5 - 7, etc....

    // A filled position can never be an option

    // Is being distributed cycliclly
    for (i = my_rank; i < boardSize; i += comm_sz)
    {
        // board
        int *coords = convertCoords(i, sidelen);
        int row = coords[0];
        int col = coords[1];

        if ((board[row][col] == 0))
        {
            printf("RANK: [%d], MOV: [%d]\n", my_rank, i);
            board[row][col] = 1; // Our next move
            int currentWinstate = win(sidelen, board, my_rank, comm_sz);
            int tempScore = -minimax(sidelen, board, -1, currentWinstate, my_rank, comm_sz); // TODO: Minimax needs to accomadate 2D array

            board[row][col] = 0; // reset board

            if (tempScore > score)
            {
                score = tempScore;
                move = i;
            }
        }
        else
        {
            continue;
        }
    }
    MPI_Reduce(&move, &finalBest, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); // TODO: Error over here

    // returns a score based on minimax tree at a given node.
    if (my_rank == 0)
    {
        int bestMov[2] = {0, 0};

        printf("Final best: %d\n", finalBest);

        bestMov[0] = convertCoords(finalBest, sidelen)[0];
        bestMov[1] = convertCoords(finalBest, sidelen)[1];

        board[bestMov[0]][bestMov[1]] = 1; // Make this the best move
    }
    MPI_Bcast(&board[0][0], 1, MPI_INT, 0, MPI_COMM_WORLD); // make sure all nodes know the board state
}

void playerMove(int sidelen, int (*board)[sidelen])
{
    // Conducts a player move in matrix

    int move = 0;
    int coords[2] = {0};
    int boardSize = sidelen * sidelen;
    do
    {
        printf("\nInput move ([0..%d])", boardSize - 1); // Where boardSize is the maximum size
        scanf("%d", &move);
        printf("\n");
        coords[0] = convertCoords(move, sidelen)[0];
        coords[1] = convertCoords(move, sidelen)[1];
    } while ((move >= boardSize) || move < 0 || board[coords[0]][coords[1]] != 0);
    board[coords[0]][coords[1]] = -1;
    MPI_Bcast(&board[0][0], 1, MPI_INT, 0, MPI_COMM_WORLD); // make sure all nodes know the board state
}

void initBoard(int sidelen, int (*board)[sidelen])
{
    // Initializes a board (as a matrix)
    for (int i = 0; i < sidelen; i++)
    {
        for (int j = 0; j < sidelen; j++)
        {
            board[i][j] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int my_rank;
    int comm_sz;
    // int SIZE = BOARDSIZE; // Default BoardSize is 9
    int boardSize = DEFAULT_BOARDSIZE;
    int sideLen = DEFAULT_SIDELEN;

    int player = 0;

    if ((argc < 2) || (argc > 4))
    {
        printf("usage: <side length> or <side length> <verbose>\n ");
        exit(1);
    }
    else
    {
        int sl = atoi(argv[1]);
        if (sl % 2 == 0)
        {
            printf("\nside length must be odd\n");
            exit(1);
        }
        boardSize = sl * sl;
        sideLen = sl;
    }

    MPI_Init(&argc, &argv); // sets up the MPI. Always this line!
    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int board[sideLen][sideLen];

    unsigned turn;

    if (my_rank == 0) // Only root node runs main thing
    {
        initBoard(sideLen, board); // init board only in root node

        printf("\n");
        // computer squares are 1, player squares are -1.
        printf("Computer: O, You: X\nPlay (1)st or (2)nd? ");
        player = 0;

        printf("\n");
        scanf("%d", &player);
        printf("\n");
    }
    MPI_Bcast(&player, 1, MPI_INT, 0, MPI_COMM_WORLD); // make sure all nodes know who the player is

    MPI_Bcast(&board[0][0], 1, MPI_INT, 0, MPI_COMM_WORLD); // make sure all nodes know the board state

    for (turn = 0; (turn < boardSize && win(sideLen, board, my_rank, comm_sz) == 0); ++turn)
    {

        if ((turn + player) % 2 == 0)
        {
            computerMove(sideLen, board, my_rank, comm_sz);
            // make sure all boards are updated at the end we may need a method for this
        }
        else
        {
            if (my_rank == 0)
            {
                playerMove(sideLen, board);
            }
        }
        // should broadcast board as a result of either move

        if (my_rank == 0)
        {
            draw(sideLen, board);
        }

        MPI_Bcast(&board[0][0], 1, MPI_INT, 0, MPI_COMM_WORLD); // make sure all nodes know the board state
    }

    switch (win(sideLen, board, my_rank, comm_sz))
    {
    case 0:
        printf("A draw. How droll.\n");
        break;
    case 1:
        draw(sideLen, board);
        printf("You lose.\n");
        break;
    case -1:
        printf("You win. Inconceivable!\n");
        break;
    }

    MPI_Finalize();
    // please no MPI stuff after this line
    return 0;
}