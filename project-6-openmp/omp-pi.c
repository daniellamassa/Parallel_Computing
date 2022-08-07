#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argc, char *argv[])
{
  int SIZE = 100;
  int nthreads = 1;
  if (argc > 4){
    printf("usage: vectors <procs> <size> or vectors <procs> <size> <seed>\n ");
    exit(1);
  }
  else {
      if (argc > 1)
        nthreads = strtol(argv[1],NULL,10);
      if (argc > 2)
        SIZE = atoi(argv[2]); //atoi converts a string to an int
      if (argc > 3)
        srand48(atoi(argv[3]));
      else
        srand48(time(NULL));
  }
  printf("threads: %d, vector size: %d\n",nthreads,SIZE);

  double startTime = omp_get_wtime();
  long long int N = SIZE;
  long double dx = 1/(double)N;
  long double sum = 0.0;
  #pragma omp parallel for num_threads(nthreads) reduction(+:sum)
    for (int i = 1; i < N; i++){
      long double w = dx;
      long double xval = i*dx;
      long double h = sqrt(1-(xval * xval));
      sum += w*h;
    }
  long double pi = 4*sum;
  double endTime = omp_get_wtime();
  printf("Time: %f\n", endTime - startTime);
  printf("Pi: %.10Lf\n",pi);



}
