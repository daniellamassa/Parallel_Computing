#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

void randomize_matrix (double * MAT, int ROWS, int COLS){
  int row,col;
  unsigned short xi[3] = {1,9,99};
  for (row = 0; row < ROWS; row++ ) {
    for (col = 0; col < COLS; col++) {
      MAT[row*COLS + col] = erand48(xi);
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

void add_matrix(double * MAT1, double * MAT2, double * MAT3, int ROWS, int COLS, int nthreads, int chunksize){
  int row,col;
  #pragma omp parallel for num_threads(nthreads) collapse(2) schedule (dynamic, chunksize)
    for (row = 0; row < ROWS; row++ ) {
      for (col = 0; col < COLS; col++) {
          MAT3[row*COLS + col] = MAT1[row*COLS + col] + MAT2[row*COLS + col];
      }
    }
}

void transpose_matrix(double * MAT, double * NEW_MAT, int ROWS, int COLS, int nthreads, int chunksize){
  int row,col;
  #pragma omp parallel for num_threads(nthreads) collapse(2) schedule (dynamic, chunksize)
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
  int nthreads = 1;
  int chunksize = 1;

  // THIS WILL BE YOUR RANDOM SEED
  // YES IT IS NON-RANDOM - Read the lab!

  if (argc != 4){
    printf("usage: matrices <threads> <rows & cols> <chunks> \n ");
    exit(1);
  }
  else{
      nthreads = strtol(argv[1],NULL,10);
      ROWS = atoi(argv[2]);
      COLS = atoi(argv[2]);
      chunksize = atoi(argv[3]);
      //printf("Rows: %d, Cols: %d, Threads: %d, Chunks: %d\n",ROWS,COLS,nthreads,chunksize);
  }

//use row-major 1D arrays to store 2D arrays
double * MAT1 =  calloc(ROWS*COLS,sizeof(double));
double * MAT2 =  calloc(ROWS*COLS,sizeof(double));
double * MAT3 =  calloc(ROWS*COLS,sizeof(double));
double * MAT4 =  calloc(ROWS*COLS,sizeof(double));


randomize_matrix(MAT1,ROWS,COLS);
randomize_matrix(MAT2,ROWS,COLS);
//print_matrix(MAT1,ROWS,COLS);
//print_matrix(MAT1,ROWS,COLS);

nthreads = 4;
chunksize = 100;

printf("SIZE: %d\n",ROWS);
for (int i = 1; i <= nthreads; i++){
  for (int c =1; c<= chunksize; c*=10){
    printf("Threads: %d, Chunks: %d\n",i,c);
    double startTime = omp_get_wtime();
    //add_matrix(MAT1,MAT2,MAT3,ROWS,COLS,i,c);
    transpose_matrix(MAT1,MAT4,ROWS,COLS,i,c);
    double endTime = omp_get_wtime();
    printf("Time: %f\n", endTime - startTime);
  }
}

/*
add_matrix(MAT1,MAT2,MAT3,ROWS,COLS,nthreads,chunksize);
print_matrix(MAT3,ROWS,COLS);
transpose_matrix(MAT1,MAT4,ROWS,COLS,nthreads,chunksize);
print_matrix(MAT4,ROWS,COLS);

double startTime = omp_get_wtime();
//add_matrix(MAT1,MAT2,MAT3,ROWS,COLS);
transpose_matrix(MAT1,MAT4,ROWS,COLS);
double endTime = omp_get_wtime();
printf("Time: %f\n", endTime - startTime)*/


 //free(MAT); //don't FREE! C99 takes care of it if allocated like this
 //(instead of via malloc)
}
