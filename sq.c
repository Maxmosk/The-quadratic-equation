#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#define ACCURACY 0.001

/*
@brief The function for deriving solutions of a quadratic equation
@detailed This function gets the number of solutions and up to two solutions, the output is "No solutions"
@param QoS number of output solutions
@param sol_1 the first output solution
@param sol_2 the second output solution
*/
void output(int QoS, float sol_1, float sol_2);

/*
@brief The function for finding the solutions of a quadratic equation
@detailed This function solves a quadratic equation by coefficients using a discriminant, writes the solutions to an array passed by a pointer and returns the number of solutions found
@param a,  b, ccoefficients of the quadratic equation in descending order of degree
@param *sol pointer to an array for solutions
@return Returns the number of solutions
@throw If the number of solutions is infinite, it returns -1
*/
int solveQuad(float a, float b, float c, float sol[2]);

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
    if (quantity_of_solutions == -2)
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

void output(int QoS, float sol_1, float sol_2)
{

    if (QoS == 0)
        printf("No solutions");
    else if (QoS == 1)
        printf("%f", sol_1);
    else if (QoS == 2)
    {
        printf("%f\n%f", sol_1, sol_2);
    }
    else if (QoS == -1)
    {
        printf("All real numbers");
    }
}

int solveQuad(float a, float b, float c, float *sol)
{
    // checking the pointer for a null pointer
    assert(sol != NULL);
    if (! (sol != NULL))
    {
    	errno = EFAULT;
    	return -2;
    }
    
    assert( ! ((isnan(a) || isinff(a)) || (isnan(b) || isinff(b)) || (isnan(c) || isinff(c))) );
    if ((isnan(a) || isinff(a)) || (isnan(b) || isinff(b)) || (isnan(c) || isinff(c)))
    {
    	errno = EDOM;
    	return -2;
	}
    
    // in the case of a linear equation
    if (abs(a) < ACCURACY)
    {
        if (abs(b) > ACCURACY)
        {
            sol[0] = -c/b;
            return 1;
        }
        else if ((abs(c) < ACCURACY) && (abs(b) < ACCURACY))
            return -1;
        else
            return 0;
    }
    // solving a linear equation with a discriminant
    float D = b*b - 4*a*c;
    assert(!isinff(D));
    if (D < 0)
        return 0;
    else if (abs(D) < ACCURACY)
    {
        sol[0] = -b / (2*a);
        return 1;
    }
    else
    {
        sol[0] = (-b + sqrtf(D)) / (2*a);
        sol[1] = (-b - sqrtf(D)) / (2*a);
        return 2;
    }
}
