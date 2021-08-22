#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include "solver.h"
#define INF_SOLS -1
#define SOL_ERR -2
#define ACCURACY 0.001
#define bool int

int main()
{
    // input of initial data
    printf("Enter the coefficients of the quadratic equation\n");
    float a=0, b=0, c=0;
    int QoN=0;
    QoN = scanf("%f%f%f", &a, &b, &c);
    if (QoN != 3)
    {
    	printf("Incorrect input");
    	return 0;
	}
	
    float solutions [2]; // array for solutions
    errno = 0;
    int quantity_of_solutions = solveQuad(a, b, c, solutions);
    if (quantity_of_solutions == SOL_ERR)
    {
    	switch(errno)
		{
    		case EDOM:
    			printf("Error domain");
    			break;
    		case EFAULT:
    			printf("Bad adress");
    			break;
		}
	}
	
    output(quantity_of_solutions, solutions [0], solutions [1]);
    getchar();
    return 0;
}

