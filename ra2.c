/* back to using malloc! Cleaner valgrind output! */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc!=2) {
		printf("Error. Pls supply argument (integer: quantity of numbers).\n");
		exit(EXIT_FAILURE);
	}
   int i, q=atoi(argv[1]);

   float *a=malloc(q*sizeof(float));

   float hoveraround=100.; // essentially, the mean
   float effectsize=3.; // isze of the random effect

   for(i=0;i<q;++i) 
       a[i]= hoveraround + effectsize * (-.5 + (float)rand()/RAND_MAX);

   // printf("%i random numbers:\n", q);
   printf("%i random numbershovering around 100 (effect size=%2.2f):\n", q, effectsize);
   for(i=0;i<q;++i) 
        printf("%4.6f ", a[i]);
   printf("\n");

   free(a);
   return 0;
}
