#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>

/*

*/


int main(int argc, char *argv[])
{

  //printf ("sizeof unsigned long: %lu",sizeof(unsigned long));
  //printf ("sizeof unsigned long long: %lu",sizeof(unsigned long long));
  unsigned long long bignumber = 996004;
  unsigned long i;
  unsigned int counter;


  clock_t startTime = clock();
  for (i = 3; i < bignumber; i+= 2)
  {
    if ((bignumber % i) == 0)
    {
      printf("I found %lu\n",i);
      counter ++;
    }
  }
  for (i = 3; i < bignumber; i++)
  {
    if (i*i == bignumber)
    {
      printf("Perfect Square With Factor %lu\n",i);

      break;
    }
  }
  printf("Total Count of Odd Divisors: %d\n", counter);

  if (counter == 0)
  {
    printf("Prime Number.\n");
  }
  else
  {
    printf("Not a Prime Number.\n");
  }
  clock_t endTime = clock();
  double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
  printf("that took %f ms\n",elapsed);
}
