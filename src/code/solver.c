#define NDEBUG
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"

/* accuracy to compare numbers */
static const double ACCURACY = 0.001f;

int is_zero (double nmb)
{
    return fabs(nmb) < ACCURACY;
}

void print_solution (int status, double sol_1, double sol_2)
{
    switch (status)
    {
        case ZERO_SOL:
            printf ("No solutions\n");
            break;
            
        case ONE_SOL:
            printf ("%.3lf\n", sol_1);
            break;
            
        case TWO_SOL:
            printf ("%.3lf %.3lf\n", sol_1, sol_2);
            break;
            
        case INF_SOLS:
            printf ("All real numbers\n");
            break;
            
        default:
            break;
        
    }
    
}

solver_code solve_linear(double k, double b, double *sol)
{
    /* checking the pointer for a null pointer */
    assert(sol);
    if (!sol)
    {
        errno = EFAULT;
        return SOL_ERR;
    }
    
    bool corr_data = ( isfinite (k) && isfinite (b) );
    
    assert(corr_data);
    if (!corr_data)
    {
        errno = EDOM;
        return SOL_ERR;
    }
    
    if (!is_zero (k))
        {
            *sol = -b/k;
            return ONE_SOL;
        }
        
        else if (is_zero (b) && is_zero (k))
            return INF_SOLS;
        
        else
            return ZERO_SOL;
}

solver_code solve_quad (double a, double b, double c, double *sol_1, double *sol_2)
{
    /* checking the pointer for a null pointer */
    assert(sol_1 && sol_2);
    if (!sol_1 || !sol_2)
    {
        errno = EFAULT;
        return SOL_ERR;
    }
    
    *sol_1 = NAN;
    *sol_2 = NAN;
    
    bool corr_data = isfinite (a) && isfinite (b) && isfinite (c);
    
    assert(corr_data);
    if (!corr_data)
    {
        errno = EDOM;
        return SOL_ERR;
    }
    
    /* in the case of a linear equation */
    if (is_zero (a))
    {
        return solve_linear (b, c, sol_1);
    }
    
    /* solving a quadratic equation with a discriminant */
    
    double b_sq = b*b;
    bool corr_b_sq = isfinite (b_sq);
    
    assert(corr_b_sq);
    if (!corr_b_sq)
    {
        errno = ERANGE;
        return SOL_ERR;
    }
    
    double ac = -4*a*c;
    bool corr_b_ac = isfinite (ac);
    
    assert(corr_b_ac);
    if (!corr_b_ac)
    {
        errno = ERANGE;
        return SOL_ERR;
    }
    
    double D = b_sq + ac;
    bool corrD = isfinite (D);
    
    assert(corrD);
    if (!corrD)
    {
        errno = ERANGE;
        return SOL_ERR;
    }
    
    if (D < 0)
        return ZERO_SOL;
    else if (is_zero (D))
    {
        *sol_1 = -b / (2*a);
        return ONE_SOL;
    }
    else
    {
        double sD = sqrt (D);
        *sol_1 = (-b - sD) / (2*a);
        *sol_2 = (-b + sD) / (2*a);
        return TWO_SOL;
    }
}

const char *get_err_codes (int e_no)
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

