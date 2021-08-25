#include <stdio.h>
#include <math.h>
#define NDEBUG
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include "solver.h"

const float ACCURACY = 0.001;

void output(int QoS, float sol_1, float sol_2)
{
    switch(QoS)
    {
        case ZERO_SOL:
            printf("No solutions");
            break;
        case ONE_SOL:
            printf("%f", sol_1);
            break;
        case TWO_SOL:
            printf("%f\n%f", sol_1, sol_2);
            break;
        case INF_SOLS:
            printf("All real numbers");
            break;
            
        default:
            printf("Unknown error with the code %d", QoS);
        
    }
    
}

int solveQuad(float a, float b, float c, float *sol_1, float *sol_2)
{
    // checking the pointer for a null pointer
    assert( (sol_1 != NULL) && (sol_2 != NULL) );
    if (! (sol_1 != NULL) && (sol_2 != NULL))
    {
        errno = EFAULT;
        return SOL_ERR;
    }
    
    bool corr_data = ( isfinite(a) && isfinite(b) && isfinite(c) );
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
            *sol_1 = -c/b;
            return ONE_SOL;
        }
        else if (isZero(c) && isZero(b))
            return INF_SOLS;
        else
            return ZERO_SOL;
    }
    // solving a quadratic equation with a discriminant
    float D = b*b - 4*a*c;
    
    bool corrD = isfinite(D);
    assert(corrD);
    if (! corrD)
    {
        errno = ERANGE;
        return SOL_ERR;
    }
    
    if (D < 0)
        return ZERO_SOL;
    else if (isZero(D))
    {
        *sol_1 = -b / (2*a);
        return ONE_SOL;
    }
    else
    {
        float sD = sqrtf(D);
        *sol_1 = (-b - sD) / (2*a);
        *sol_2 = (-b + sD) / (2*a);
        return TWO_SOL;
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
        
        default:
            return "Unknown error";
    }
}
