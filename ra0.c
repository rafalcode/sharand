/* no dynamic memory */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc!=2) {
		printf("Error. Pls supply argument (integer: quantity of numbers).\n");
		exit(EXIT_FAILURE);
	}
   int i, q=atoi(argv[1]);

   float a[q];

   for(i=0;i<q;++i) 
       a[i]=(float)rand()/RAND_MAX;

   printf("%i random numbers:\n", q);
   for(i=0;i<q;++i) 
        printf("%4.6f ", a[i]);
   printf("\n");

   return 0;
}
