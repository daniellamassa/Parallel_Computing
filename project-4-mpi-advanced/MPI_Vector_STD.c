#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
//to run (simple): mpirun ./MPI_blank

void print_vector(int *vec, int size){ //function needs a pointer or array of type double, and its size
  int index;
  for (index= 0; index< size; index++ ){ //while index < size
    printf("%d ", vec[index]);  //print the floating point (double) value at that index
}
  return; //return nothing
}

int * randomize_vector_p(int *vec, int size, int my_rank){
	int LOWER = 0;
	int UPPER = 100;
  int *p; //declare pointer of type double
  int * vec_end = vec+size; //points to the end of the array
  for (p= vec; p < vec_end; p++){ //while p < end of the array
    *p = rand()%(UPPER - LOWER +1) + LOWER; //set the value at the pointer to a random int
  }
  return vec;
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

	int SIZE;
  SIZE = atoi(argv[1]); //atoi converts a string to an int
  int slice_size = SIZE/comm_sz;

  if (SIZE%comm_sz == 0){

    int *my_vector =  calloc(slice_size,sizeof(int));
    srand(my_rank+5);
    my_vector = randomize_vector_p(my_vector,slice_size, my_rank);
  	int local_sum = 0;
    int global_sum = 0;

    //print_vector(my_vector,slice_size);
    //printf("\n");

    for (int i = 0; i < slice_size; i++){
      local_sum += my_vector[i];
    }
    //printf("task %d sum: %d\n",my_rank,local_sum);

    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    double global_mean = (double) global_sum/(SIZE);
    //printf("global mean: %f\n",global_mean);

    double local_sum_sq_diff = 0;
    for (int i = 0; i < slice_size; i++){
      double temp = pow((double) my_vector[i] - global_mean,2);
      local_sum_sq_diff += temp;
    }
    //printf("local sum square diff: %f\n",local_sum_sq_diff);

    double global_sum_of_sq_diff = 0;
    MPI_Reduce(&local_sum_sq_diff, &global_sum_of_sq_diff, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    //printf("global sum square diff: %f\n",global_sum_of_sq_diff);
    if (my_rank == 0) {
      double sd = sqrt(global_sum_of_sq_diff/SIZE);
      clock_t endTime = clock();
      double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
      printf("that took %f ms\n",elapsed);
      printf("standard deviation: %f\n",sd);
    }
  }
  else{
    if (my_rank == 0){
      printf("Vector size is not evenly divisible by the number of processors. Please try again.\n");
      exit(1);
    }
  }

	MPI_Finalize();
	//please no MPI stuff after this line
	return 0;
}
