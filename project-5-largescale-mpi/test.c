// #include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> //for random seed
#include <math.h> //need to compile with -m
#include <mpi.h>
// to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
// to run (simple): mpirun ./MPI_blank

// #define SIDELEN 3

char gridChar(int i){
    switch (i)
    {
    case -1:
        return 'X';
    case 1:
        return 'O';
    default:
        return ' ';
    }
}

int wStraight (int sidelen, int (*board)[sidelen], int my_rank, int comm_sz){

  //row checking
  for (int row = my_rank; row < sidelen; row+=comm_sz){
    bool rWin = true;
    int curX = board[row][0];

    for (int pos = 1; pos < sidelen; pos++){
      int nextX = board[row][pos];

      if (curX != nextX || nextX == 0 || curX == 0){
        rWin = false;
        break;
      }
    }
    if (rWin == true){
      printf("win found at task %d at row: %d\n",my_rank,row);
      return curX;
    }
  }

  //column checking
  for (int col = my_rank; col < sidelen; col+= comm_sz){
    bool cWin = true;
    int curX = board[0][col];

    for (int pos = 1; pos <sidelen; pos++){
      int nextX = board[pos][col];

      if (curX != nextX || nextX == 0 || curX == 0){
        cWin = false;
        break;
      }
    }
    if (cWin == true){
      printf("win found at task %d at column: %d\n",my_rank,col);
      return curX;
    }
  }

  return 0;


}

int wH(int sidelen, int (*board)[sidelen]){
    int totalStraights = sidelen * 2;
    int size = sidelen * sidelen;

    int curX = board[0][0];
    int curY = board[0][0];

    // Always runs sidelen**2 times
    for (int col = 0; col < sidelen; col++){
        int nxt = 1;
        for (int row = 0; row < sidelen; row++){
            if (row == 0){
                curY = board[row][col];
            }

            if (nxt == 1){
                curX = board[col][row];
                nxt = 0;
            }

            if (curX != 0){
                if (curX == board[col][row]){
                    printf(" Current X val: (%d), board[%d][%d]\n", curX, col, row);
                    curX = board[col][row];
                }
                else{
                    printf("Currently detected X: %d at board[%d][%d]\n", board[col][row], col, row);
                    curX = 0;
                }
            }

            if (curY != 0){
                if (curY == board[row][col]){
                    // printf(" Current Y val: (%d), board[%d][%d]\n", curY, row, col);
                    curY = board[row][col];
                }
                else{
                    // printf("Currently detected Y: %d at board[%d][%d]\n", board[row][col], row, col);
                    curY = 0;
                }
            }
        }
        if (nxt == 0){
            nxt += 1;
        }
        // return winner
        if (curX != 0 && curY == 0){
            return curX;
        }
        else if (curX == 0 && curY != 0){
            return curY;
        }
    }
    return 0;
}

int wD(int sidelen, int (*board)[sidelen])
{

    int fwd = 0;
    int bkwd = 0;

    int iF = board[0][0];
    int iB = board[0][sidelen - 1];

    for (int i = 0; i < sidelen; i++){

        if (iF != 0){ // getting "\" diagonal
            if (iF == board[i][i]){
                iF = board[i][i];
            }
            else{
                iF = 0;
            }
        }

        if (iB != 0){ // getting "/" diagonal
            if (iB == board[i][(sidelen - 1) - i]){
                iB = board[i][(sidelen - 1) - i];
            }
            else{
                iB = 0;
            }
        }
    }

    if (iF != 0 && iB == 0){
        printf("IF: %d\n", iF);

        return iF;
    }
    else if (iF == 0 && iB != 0){
        printf("IF: %d\n", iB);

        return iB;
    }
    else{
        //printf("EVIDENTLY NO\n");

        return 0;
    }
}

int win(int sidelen, int (*board)[sidelen], int my_rank, int comm_sz){
    // check if board size is legal
    if (sidelen % 2 == 0){
        printf("\n[Error] Side Length cannot be even\n");
        exit(1);
    }

    int horz = wStraight(sidelen, board, my_rank, comm_sz);
    int diag = wD(sidelen, board);
    printf("DIAG: %d", diag);

    if (diag != 0 && horz == 0){
        return diag;
    }
    else if (diag == 0 && horz != 0){
        return horz;
    }
    else{
        return 0; // Default return value
    }
}

int draw(int sidelen, int (*board)[sidelen]){
    for (int i = 0; i < sidelen; i++){
        for (int j = 0; j < sidelen; j++){
            if (j == sidelen - 1){
                printf(" %c \n", gridChar(board[i][j]));
                if (i != sidelen - 1){
                    // print a bar underneath
                    for (int k = 0; k < sidelen - 1; k++){
                        printf("---+");
                    }
                    printf("---\n");
                }
            }
            else{
                printf(" %c |", gridChar(board[i][j]));
            }
        }
    }
}

void testSuite(int sidelen, int (*board)[sidelen]){
    // Test both diagonals

    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", i, i);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[i][i] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int test = win(sidelen, board);
    printf("\nTest 1: %d\n", test);

    // =============================================

    for (int i = 0; i < sidelen; i++){ // row
        for (int j = 0; j < sidelen; j++){ // col
            board[i][j] = 0;
        }
    }
    
    // ==============================================


    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", i, sidelen-i);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[i][(sidelen-1)-i] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int test2 = win(sidelen, board);
    printf("\nTest 2: %d\n", test2);


    // =============================================

    for (int i = 0; i < sidelen; i++){ // row
        for (int j = 0; j < sidelen; j++){ // col
            board[i][j] = 0;
        }
    }
    
    // ==============================================

    // Test all rows

    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", 0, i);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[0][i] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int testrow1 = win(sidelen, board);
    printf("\nTest 3: %d\n", testrow1);

    // =============================================

    for (int i = 0; i < sidelen; i++){ // row
        for (int j = 0; j < sidelen; j++){ // col
            board[i][j] = 0;
        }
    }
    
    // ==============================================


    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", 1, i);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[1][i] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int testrow2 = win(sidelen, board);
    printf("\nTest 4: %d\n", testrow2);

    // =============================================

    for (int i = 0; i < sidelen; i++){ // row
        for (int j = 0; j < sidelen; j++){ // col
            board[i][j] = 0;
        }
    }
    
    // ==============================================

    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", 2, i);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[2][i] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int testrow3 = win(sidelen, board);
    printf("\nTest 5: %d\n", testrow3);

    // =============================================

    for (int i = 0; i < sidelen; i++){ // row
        for (int j = 0; j < sidelen; j++){ // col
            board[i][j] = 0;
        }
    }
    
    // ==============================================

    // Check all columns ============================

    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", i, 0);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[i][0] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int testcol1 = win(sidelen, board);
    printf("\nTest 6: %d\n", testcol1);

    // =============================================

    for (int i = 0; i < sidelen; i++){ // row
        for (int j = 0; j < sidelen; j++){ // col
            board[i][j] = 0;
        }
    }
    
    // ==============================================


    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", i, 1);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[i][1] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int testcol2 = win(sidelen, board);
    printf("\nTest 7: %d\n", testcol2);

    // =============================================

    for (int i = 0; i < sidelen; i++){ // row
        for (int j = 0; j < sidelen; j++){ // col
            board[i][j] = 0;
        }
    }
    
    // ==============================================

    for (int i = 0; i < sidelen; i++){ // row
        printf("Current Idx :[%d][%d]\n", i, 2);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[i][2] = -1; // Wins "|"
    }
    draw(sidelen, board);
    int testcol3 = win(sidelen, board);
    printf("\nTest 8: %d\n", testcol3);
}

int main(int argc, char *argv[]){

    // MPI CODE


    int comm_sz; /* Number of processes    */
    int my_rank; /* My process rank        */
    // Don't put any MPI stuff before this line
    MPI_Init(&argc, &argv); // sets up the MPI. Always this line!
    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // ==============================





    int SIDELEN = 3;

    if ((argc < 2) || (argc > 4)){
        printf("usage: <side length> or <side length> <verbose>\n ");
        exit(1);
    }
    else{
        int sl = atoi(argv[1]);
        if (sl % 2 == 0){
            printf("\nside length must be odd\n");
            exit(1);
        }

        if (sl <= 1){
            printf("\n side length must be greater than 1 \n");
            exit(1);
        }
        SIDELEN = sl;
    }

    int board[SIDELEN][SIDELEN]; // Made into multidimensional array

    for (int i = 0; i < SIDELEN; i++){ // row
        for (int j = 0; j < SIDELEN; j++){ // col
            board[i][j] = 0;
        }
    }

    for (int i = 0; i < SIDELEN; i++){ // row
        printf("Current Idx :[%d][%d]\n", i, i);
        // board[i][(SIDELEN - 1) - i] = -1; // Wins "/"
        board[i][5] = -1; // Wins "|"
    }
    if (my_rank == 0){
      draw(SIDELEN, board);
    }

    int test = win(SIDELEN, board, my_rank, comm_sz);
    printf("\nTest: %d\n", test);




    // MPI

    MPI_Finalize();

    // ========================

    return 0;
}
