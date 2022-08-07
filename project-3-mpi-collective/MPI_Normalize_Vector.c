#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
//to run (simple): mpirun ./MPI_blank

void print_vector(double *vec, int size){ //function needs a pointer or array of type double, and its size
  int index;
  for (index= 0; index< size; index++ ){ //while index < size
    printf("%f ", vec[index]);  //print the floating point (double) value at that index
}
  return; //return nothing
}

double * randomize_vector_p(double *vec, int size){
  double *p; //declare pointer of type double
  double * vec_end = vec+size; //points to the end of the array
  for (p= vec; p < vec_end; p++){ //while p < end of the array
    *p = (double) rand()/rand(); //set the value at the pointer to a random double
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
	double *original_vector =  calloc(SIZE,sizeof(double));
	double *result_vector =  calloc(SIZE,sizeof(double));
  double *slice =  calloc(slice_size,sizeof(double));

	double local_sum = 0;
  double magnitude = 0;

  if (SIZE%comm_sz == 0){
    if (my_rank == 0){ //i am root.
    original_vector = randomize_vector_p(original_vector, SIZE); //fill with data.
    //printf("Original Vector:\n");
    //print_vector(original_vector, SIZE);
  	//printf("\n");
    }
  }
  else{
    printf("Vector size is not evenly divisible by the number of processors. Please try again.");
    exit(1);
  }
  MPI_Scatter(original_vector,slice_size,MPI_DOUBLE,slice,slice_size,MPI_DOUBLE,0,MPI_COMM_WORLD);
  //print_vector(slice,slice_size);
  //printf("\n");
  for (int i = 0; i < slice_size; i++){
    local_sum += slice[i] * slice[i];
  }
  if (my_rank != 0){
		MPI_Send(&local_sum,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	else{ //i am root.
		double othersum;
		for (int q = 1; q < comm_sz; q++){
					MPI_Recv(&othersum,1,MPI_DOUBLE,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					local_sum += othersum;
		}
    magnitude = sqrt(local_sum);
  }

  MPI_Bcast(&magnitude,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
  for (int z = 0; z < slice_size; z++){
    slice[z] = slice[z]/magnitude;
  }
  MPI_Gather(slice,slice_size,MPI_DOUBLE,result_vector,slice_size,MPI_DOUBLE,0,MPI_COMM_WORLD);

  if (my_rank == 0){ //i am root.
    //printf("Normalized Vector:\n");
    //print_vector(result_vector, SIZE);
    //printf("\n");
    double test_case_mag = 0;
    double test_case_sum = 0;
    for (int p = 0; p < SIZE; p++){
      test_case_sum += result_vector[p] * result_vector[p];
    }
    test_case_mag = sqrt(test_case_sum);
    clock_t endTime = clock();
    double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
    printf("that took %f ms\n",elapsed);
    printf("Magnitude of Normalized Vector (test case): %f \n", test_case_mag);

  }

	MPI_Finalize();
	//please no MPI stuff after this line
	return 0;
}
