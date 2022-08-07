#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
vectors.c for week 1 bootcamp
author: John Rieffel

*/

//argc is the argument count from the commandline
//argc is always at least 1, because the excutable
//is an argument
//
//each argument is held in a separate string.
//argv is an *array* of strings

double * randomize_vector(double *vec, int size) //function needs pointer or array of type double, and its size
{
  int index;
  for (index= 0; index< size; index++ ) { //while index < size,
   vec[index] = drand48();  //set the value at that index to a random double
  }
  return vec; // return the randomized array
}

double * randomize_vector_p(double *vec, int size)
{
  double *p; //declare pointer of type double
  double * vec_end = vec+size; //points to the end of the array
  for (p= vec; p < vec_end; p++){ //while p < end of the array
    *p = drand48(); //set the value at the pointer to a random double
  }
  return vec;

}


void print_vector(double *vec, int size) //function needs a pointer or array of type double, and its size
{
  int index;
  for (index= 0; index< size; index++ ) { //while index < size
    printf("%f ", vec[index]);  //print the floating point (double) value at that index
}

  return; //return nothing
}

void print_vector_p(double *vec, int size)
{
  double *p;
  double * vec_end = vec+size;
  for (p = vec; p < vec_end; p++)
  {
    printf("%f ", *p);
  }

}

void add_vectors (double *vec1, double *vec2, int size){
  // C[i] = A[i]+B[i]
  double * new_vec = calloc(size,sizeof(double));
  double *p1 =  vec1; //pointer for vector 1
  double *p2 = vec2; //pointer for vector 2
  double *p3 = new_vec; //pointer for new vector
  double * vec_end = new_vec+size; //points to the end of the array
  for (p3= new_vec; p3 < vec_end; p3++){
    *p3 = *p1 + *p2; //put sum value into new_vec
      p1++;
      p2++;
  }
  print_vector(new_vec, size);

}

double vector_dot_product (double *vec1, double *vec2, int size){
  // sum += A[i]*B[i]
  double sum_of_products = 0.0; //to return
  double *p1 =  vec1; //pointer for vector 1
  double *p2 = vec2; //pointer for vector 2
  double * vec_end = p1+size; //points to the end of the array
  for (p1 =  vec1; p1 < vec_end; p1++){
    double product = *p1 * *p2; //find product the current array values
    //printf("current p: %f",product);    debugging
    //printf("\n");
    sum_of_products += product; //add product to total
    p2++;
  }
  return sum_of_products;
}

int main(int argc, char *argv[])
{
  int SIZE = 0;
  clock_t startTime = clock();

  if ((argc < 2) || (argc > 3)){
    printf("usage: vectors <size> or vectors <size> <seed>\n ");
    exit(1);
  }
  else {
      SIZE = atoi(argv[1]); //atoi converts a string to an int
      printf("size: %d\n",SIZE);
      if (argc == 3)
        srand48(atoi(argv[2]));
      else
        srand48(time(NULL));
  }

//calloc(number of elements, size of elements)
//calloc, unlike malloc, zeros the allocated memory
double * vector1 =  calloc(SIZE,sizeof(double));
double * vector2 =  calloc(SIZE,sizeof(double));


vector1 = randomize_vector_p(vector1, SIZE);
vector2 = randomize_vector_p(vector2, SIZE);

print_vector(vector1, SIZE);
printf("\n");
print_vector(vector2, SIZE);
printf("\n");
clock_t endTime = clock();
double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
printf("that took %f ms\n",elapsed);

//add_vectors(vector1, vector2, SIZE);
//printf("\n");
//double product = vector_dot_product(vector1, vector2, SIZE);
//printf("product: %f",product);
//printf("\n");
}
