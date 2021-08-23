#include <stdio.h>
#include <math.h>
#define NDEBUG
#include <assert.h>
#include <errno.h>
#include "solver.h"
#define INF_SOLS -1
#define SOL_ERR -2
#define ACCURACY 0.001
#define bool char

void output(int QoS, float sol_1, float sol_2)
{
	switch(QoS)
	{
		case 0:
	        printf("No solutions");
	        break;
	    case 1:
	        printf("%f", sol_1);
	        break;
	    case 2:
	        printf("%f\n%f", sol_1, sol_2);
	        break;
	    case INF_SOLS:
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
    	return SOL_ERR;
    }
    
    bool corr_data = ! ( (isnan(a) || isinf(a)) || (isnan(b) || isinf(b)) || (isnan(c) || isinf(c)) );
    assert(corr_data);
    if (! corr_data)
    {
    	errno = EDOM;
    	return SOL_ERR;
	}
    
    // in the case of a linear equation
    if (isZero(a))
    {
        if (!isZero(b))
        {
            sol[0] = -c/b;
            return 1;
        }
        else if (isZero(c) && isZero(b))
            return INF_SOLS;
        else
            return 0;
    }
    // solving a quadratic equation with a discriminant
    float D = b*b - 4*a*c;
    
    bool corrD = !isinf(D);
    assert(corrD);
    if (! corrD)
    {
    	errno = ERANGE;
    	return SOL_ERR;
	}
	
    if (D < 0)
        return 0;
    else if (isZero(D))
    {
        sol[0] = -b / (2*a);
        return 1;
    }
    else
    {
    	float sD = sqrtf(D);
        sol[0] = (-b - sD) / (2*a);
        sol[1] = (-b + sD) / (2*a);
        return 2;
    }
}

int isZero(float nmb)
{
	return abs(nmb) < ACCURACY;
}

char* get_err_codes(int e_no)
{
	switch(e_no)
	{
    	case EDOM:
    		return "Error domain. One of the parameters is infinity or not a number";
    		break;
    	case EFAULT:
    		return "Bad adress. A null pointer was passed as a parameter";
    		break;
    	case ERANGE:
    		return "Error range. In the process of calculations, an infinitely large number was obtained";
    		break;
	}
}
