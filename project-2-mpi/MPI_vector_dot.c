#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
//to run (simple): mpirun ./MPI_blank

void print_vector(double *vec, int size) //function needs a pointer or array of type double, and its size
{
  int index;
  for (index= 0; index< size; index++ ) { //while index < size
    printf("%f ", vec[index]);  //print the floating point (double) value at that index
}
  return; //return nothing
}

double * randomize_vector(double *vec, int size) //function needs pointer or array of type double, and its size
{
  int index;
  for (index= 0; index< size; index++ ) { //while index < size,
   vec[index] = (double) rand()/rand();  //set the value at that index to a random double
  }
  return vec; // return the randomized array
}

double * randomize_vector_p(double *vec, int size)
{
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
	double *vector1 =  calloc(SIZE,sizeof(double));
	double *vector2 =  calloc(SIZE,sizeof(double));
	double local_result = 0;
	double global_result = 0;

	if (my_rank != 0){
		//recieve vectors.
		MPI_Recv(vector1,SIZE,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(vector2,SIZE,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	else{ //i am root.
			vector1 = randomize_vector_p(vector1, SIZE); //fill with data.
			vector2 = randomize_vector_p(vector2, SIZE);
			//print_vector(vector1, SIZE);
			//printf("\n");
			//print_vector(vector2, SIZE);
			//printf("\n");
			for (int other = 1; other < comm_sz; other++){ 	//send vectors to other nodes.
				MPI_Send(vector1,SIZE,MPI_DOUBLE,other,0,MPI_COMM_WORLD);
				MPI_Send(vector2,SIZE,MPI_DOUBLE,other,0,MPI_COMM_WORLD);
			}
	}
	//calculate the partial solution of vector dot product on all tasks.
	for (int i = my_rank; i < SIZE; i+=comm_sz){
		local_result += vector1[i] * vector2[i];
	}
	//printf("local vector dot product of process %d is %f\n",my_rank,local_result);

	if (my_rank != 0){
		MPI_Send(&local_result,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD); //send local result
	}
	else{ //i am root.
    global_result = local_result;
    double other_result;
		//recieve local results from non-roots and calculate global result.
		for (int q = 1; q < comm_sz; q++){
					MPI_Recv(&other_result,1,MPI_DOUBLE,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					global_result += other_result;
		}
    clock_t endTime = clock();
    double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
    printf("that took %f ms\n",elapsed);
		printf("the total vector dot product is is %f\n", global_result);
    printf("\n");
	}

	MPI_Finalize();
	//please no MPI stuff after this line
	return 0;
}
