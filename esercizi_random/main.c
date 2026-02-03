#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <time.h>

#define Z 10
int main() 
{
	int y = FLT_MAX * INT_MAX;
	
	
	srand(time(NULL));
	
	printf("TEST\n");
	double ra = rand()/RAND_MAX*1.0;
	printf("RESULTS: %f\n", ra);
	
	
}