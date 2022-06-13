/*
@mainpage The quadratic equation

This project consists of the main file main.c and external files:
1. File with functions for solving a quadratic equation (solve.h, solve.c);
2. File with functions for testing functions for solving (testing.h, testing.c)
*/

#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "solver.h"
#include "testing.h"


int main(void)
{
    #ifdef TESTS_ON
    test_func ();
    #endif
    
    /* input and chacking of initial data */
    printf("Enter the coefficients of the quadratic equation\n");
    
    double a = NAN, b = NAN, c = NAN;
    int status = 0; /* variable for quantity of inputed numbera */
    
    status = scanf ("%lf %lf %lf", &a, &b, &c);
    
    /* cheching of correct input */
    if (status != 3)
    {
        printf("Incorrect input");
        return 0;
    }
    
    double solutions [2] = {NAN, NAN}; /* array for solutions */
    errno = 0;
    solver_code quantity_of_solutions = solve_quad (a, b, c, &solutions[0], &solutions[1]);
    if (quantity_of_solutions == SOL_ERR)
    {
        printf("%s", get_err_codes(errno));
    }
    
    print_solution (quantity_of_solutions, solutions [0], solutions [1]);
    
    return 0;
}

