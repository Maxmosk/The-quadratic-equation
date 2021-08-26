#define NDEBUG
#include <assert.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include "solver.h"
#include "testing.h"

static void test_of_sol(struct sol_testing_data examp)
{
    float solutions[2] = {NAN, NAN}; // array for solutions
    errno = 0;
    enum sol_out quantity_of_solutions = solve_quad(examp.a, examp.b, examp.c, &solutions[0], &solutions[1]);
    
    if (quantity_of_solutions == examp.result)
    {
        switch(quantity_of_solutions)
        {
            case SOL_ERR:
                if ( errno == examp.errcode )
                    return;
                    
                printf("Input\na: %f\nb: %f\nc: %f\nOutput\nQoS: %d\nerrcode: %d\n\n",
                        examp.a, examp.b, examp.c, examp.result, examp.errcode);
                printf("Real output\nQoS: %d\nerrcode: %d",
                        quantity_of_solutions, errno);
                break;
                
            case ONE_SOL:
                if ( is_zero(examp.sol_1-solutions[0]) )
                    return;
                    
                printf("Input\na: %f\nb: %f\nc: %f\nOutput\nQoS: %d\nsol_1: %f\n\n",
                        examp.a, examp.b, examp.c, examp.result, examp.sol_1);
                printf("Real output\nQoS: %d\nsol_1: %f\nsol_2: %f",
                        quantity_of_solutions, solutions[0]);
                break;
                
            case TWO_SOL:
                if ( is_zero(examp.sol_1-solutions[0]) && is_zero(examp.sol_2-solutions[1]) )
                    return;
                    
                printf("Input\na: %f\nb: %f\nc: %f\nOutput\nQoS: %d\nsol_1: %f\nsol_2: %f\n\n",
                        examp.a, examp.b, examp.c, examp.result, examp.sol_1, examp.sol_2);
                printf("Real output\nQoS: %d\nsol_1: %f\nsol_2: %f",
                        quantity_of_solutions, solutions[0], solutions[1]);
                break;
            
            default:
                break;
        }
    }
    
    else
    {
        printf("Input\na: %f\nb: %f\nc: %f\nOutput\nQoS: %d\n\n",
                examp.a, examp.b, examp.c, examp.result);
        printf("Real output\nQoS: %d",
                quantity_of_solutions);
    }
}

int test_func()
{
    const struct sol_testing_data tests[] =
    {
        {1       , 2      , 1, ONE_SOL , -1 , NAN, 0     }, // 1 solution quad
        {1       , 4      , 3, TWO_SOL , -3 , -1 , 0     }, // 2 solutions quad
        {1       , 1      , 1, ZERO_SOL, NAN, NAN, 0     }, // 0 silutions quad
        {0       , 0      , 0, INF_SOLS, NAN, NAN, 0     }, // inf solutions line
        {0       , 1      , 1, ONE_SOL , -1 , NAN, 0     }, // 1 solution line
        {0       , 0      , 1, ZERO_SOL, NAN, NAN, 0     }, // 0 solutions line
        {1       , FLT_MAX, 1, SOL_ERR , NAN, NAN, ERANGE}, // inf ib D
        {INFINITY, 1      , 1, SOL_ERR , NAN, NAN, EDOM  } // inf error
    };
    
    for (int i = 0; i < sizeof(tests)/sizeof(struct sol_testing_data); i++)
        test_of_sol(tests[i]);
    
    return 0;
}
