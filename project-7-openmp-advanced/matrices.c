#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

void randomize_matrix (double * MAT, int ROWS, int COLS){
  int row,col;
  int counter = 1;
  for (row = 0; row < ROWS; row++ ) {
    for (col = 0; col < COLS; col++) {
        MAT[row*COLS + col] = drand48();
    }
  }
}

void print_matrix (double * MAT, int ROWS, int COLS){
  int row,col;
  for (row = 0; row < ROWS; row++ ) {
    for (col = 0; col < COLS; col++) {
        printf("%f ",MAT[row*COLS + col]);
    }
    printf("\n");
  }
  printf("\n");
}

void add_matrix(double * MAT1, double * MAT2, double * MAT3, int ROWS, int COLS){
  int row,col;
  for (row = 0; row < ROWS; row++ ) {
    for (col = 0; col < COLS; col++) {
        MAT3[row*COLS + col] = MAT1[row*COLS + col] + MAT2[row*COLS + col];
    }
  }
}

void transpose_matrix(double * MAT, double * NEW_MAT, int ROWS, int COLS){
  int row,col;
  for (row = 0; row < ROWS; row++ ) {
    for (col = 0; col < COLS; col++) {
        NEW_MAT[row*COLS + col] = MAT[col*ROWS + row];
    }
  }
}


int main(int argc, char *argv[])
{
  int ROWS = 0;
  int COLS = 0;
  // THIS WILL BE YOUR RANDOM SEED
  // YES IT IS NON-RANDOM - Read the lab!
  unsigned short xi[3] = {1,9,99};
  double somenum = erand48(xi);

  if (argc != 3){
    printf("usage: matrices <rows> <cols>\n ");
    exit(1);
  }
  else{
      ROWS = atoi(argv[1]);
      COLS = atoi(argv[2]);
      printf("Rows: %d, Cols: %d\n",ROWS,COLS);
  }
//use row-major 1D arrays to store 2D arrays
double * MAT1 =  calloc(ROWS*COLS,sizeof(double));
double * MAT2 =  calloc(ROWS*COLS,sizeof(double));
double * MAT3 =  calloc(ROWS*COLS,sizeof(double));
double * MAT4 =  calloc(ROWS*COLS,sizeof(double));


randomize_matrix(MAT1,ROWS,COLS);
randomize_matrix(MAT2,ROWS,COLS);

double startTime = omp_get_wtime();
//add_matrix(MAT1,MAT2,MAT3,ROWS,COLS);
transpose_matrix(MAT1,MAT4,ROWS,COLS);
double endTime = omp_get_wtime();
printf("Time: %f\n", endTime - startTime);


 //free(MAT); //don't FREE! C99 takes care of it if allocated like this
 //(instead of via malloc)
}
