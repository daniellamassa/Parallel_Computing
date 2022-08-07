#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
//to run (simple): mpirun ./MPI_blank

int CompareInts(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
//Use this in your MPI Sorting Code
void PrintArray(int *array, int asize)
{
    for (int i =0; i < asize; i++)
        printf(" %d ", array[i]);
    printf("\n");

}

//Use this in your MPI Sorting Code
void SortMySlice(int *slice, int slice_size)
{
    qsort(slice,slice_size,sizeof(int),CompareInts);
}

//swap two integers
void Swap(int *a, int *b)
{
                int tmp = *a;
                *a=*b;
                *b = tmp;
                return;
}

void MergeSlicesKeepSmallerBetter(int *myslice, int mysize, int *otherslice, int othersize)
{
  int * smallest = malloc(mysize*sizeof(int));
  int smallindex = 0;
  int myindex = 0;
  int otherindex = 0;
  while (smallindex < mysize)
  {
    int mine = myslice[myindex];
    int others = otherslice[otherindex];
    if (mine <= others)
    {
      smallest[smallindex] = mine;
      myindex++;
    }
    else{
      smallest[smallindex] = others;
      otherindex++;
    }
    smallindex++;
  }
  memcpy(myslice,smallest,mysize*sizeof(int));
  free(smallest);
  return;
}

void MergeSlicesKeepLargerBetter(int *myslice, int mysize, int *otherslice, int othersize)
{
  int * largest = malloc(mysize*sizeof(int));
  int largeindex = mysize - 1;
  int myindex = mysize - 1;;
  int otherindex = mysize - 1;
  while (largeindex >= 0)
  {
    int mine = myslice[myindex];
    int others = otherslice[otherindex];
    if (mine >= others)
    {
      largest[largeindex] = mine;
      myindex--;
    }
    else{
      largest[largeindex] = others;
      otherindex--;
    }
    largeindex--;
  }
  memcpy(myslice,largest,mysize*sizeof(int));
  free(largest);
  return;
}

void print_vector(int *vec, int size){ //function needs a pointer or array of type double, and its size
  int index;
  for (index= 0; index< size; index++ ){ //while index < size
    printf("%d ", vec[index]);  //print the floating point (double) value at that index
}
  return; //return nothing
}

int * randomize_vector_p(int *vec, int size){
	int LOWER = 0;
	int UPPER = 500;
  int *p; //declare pointer of type double
  int * vec_end = vec+size; //points to the end of the array
  for (p= vec; p < vec_end; p++){ //while p < end of the array
    *p = (rand()%(UPPER - LOWER +1)) + LOWER; //set the value at the pointer to a random int
  }
  return vec;
}

int compute_partner(bool is_even, int my_rank, int comm_sz){
  int partner;
  if (is_even == true){ //even phase
    if (my_rank % 2 != 0){ //odd rank
      partner = my_rank - 1;
    }
    else{ //even rank
      partner = my_rank + 1;
    }
  }
  else{ //odd phase
    if (my_rank % 2 != 0){ //odd rank
      partner = my_rank + 1;
    }
    else{ //even rank
      partner = my_rank - 1;
    }
  }
  if (partner == -1 || partner == comm_sz){
    partner = MPI_PROC_NULL;
  }
  return partner;
}

int main(int argc, char *argv[]){

  clock_t startTime = clock();

	int        comm_sz;               /* Number of processes    */
	int        my_rank;               /* My process rank        */
	//Don't put any MPI stuff before this line

	MPI_Init(&argc, &argv);  //sets up the MPI. Always this line!
	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	// do some stuff

	int SIZE = atoi(argv[1]); //atoi converts a string to an int
	bool is_even = false;
  SIZE = SIZE-(SIZE%comm_sz);
	int slice_size = SIZE/comm_sz;
	int *original_vector =  calloc(SIZE,sizeof(int));
  int *final_vector =  calloc(SIZE,sizeof(int));



	int *slice =  calloc(slice_size,sizeof(int));
	int *other_slice =  calloc(slice_size,sizeof(int));


	if (my_rank == 0){ //i am root.
		original_vector = randomize_vector_p(original_vector, SIZE); //fill with data.
    //printf("Original Vector:\n");
    //print_vector(original_vector, SIZE);
  	//printf("\n");
	}
	MPI_Scatter(original_vector,slice_size,MPI_INT,slice,slice_size,MPI_INT,0,MPI_COMM_WORLD);
	//print_vector(slice,slice_size);
	//printf("\n");
  SortMySlice(slice,slice_size);
  for (int phase = 0; phase < comm_sz; phase ++){
  	//printf("\n");
  	//PrintArray(slice, slice_size);
  	//printf("\n");
    int my_partner = compute_partner(is_even,my_rank,comm_sz);
    //printf("rank: %d, partner: %d\n",my_rank,my_partner);
    MPI_Sendrecv(slice,slice_size,MPI_INT,my_partner,0,other_slice,slice_size,MPI_INT,my_partner,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    //printf("Task: %d slice & other slice:\n",my_rank);
    //PrintArray(slice, slice_size);
    //printf("\n");
    //PrintArray(other_slice, slice_size);
    //printf("\n");

    if (my_partner == MPI_PROC_NULL){
      slice = slice;
    }
    else{
      if (my_rank < my_partner){
        MergeSlicesKeepSmallerBetter(slice, slice_size, other_slice, slice_size); //keep smaller
      }
      else{
        MergeSlicesKeepLargerBetter(slice, slice_size, other_slice, slice_size); //keep larger
      }
    }
    is_even = !is_even;
  }

  //printf("Task: %d slice:\n",my_rank);
  //PrintArray(slice, slice_size);
  //printf("\n");


  MPI_Gather(slice,slice_size,MPI_INT,final_vector,slice_size,MPI_INT,0,MPI_COMM_WORLD);
  if (my_rank == 0){ //i am root.
    clock_t endTime = clock();
    double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
    printf("that took %f ms\n",elapsed);
    //printf("Final Vector:\n");
    //print_vector(final_vector, SIZE);
    //printf("\n");
  }



	MPI_Finalize();
	//please no MPI stuff after this line
	return 0;
}
