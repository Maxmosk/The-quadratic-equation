/*
@mainpage The quadratic equation

This project consists of the main file main.c and external files:
1. Filt with functions for solving a quadratic equation (solve.h, solve.c);
2. File with functions for testing functions for solving (testing.h, testing.c)
*/

#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "solver.h"
#include "testing.h"

int main()
{
    test_func();
    
    // input and chacking of initial data
    printf("Enter the coefficients of the quadratic equation\n");
    
    float a = NAN, b = NAN, c = NAN;
    int status = 0; // variable for quantity of inputed numbera
    
    status = scanf("%f %f %f", &a, &b, &c);
    
    // cheching of correct input
    if (status != 3)
    {
        printf("Incorrect input");
        return 0;
    }
    
    float solutions [2] = {NAN, NAN}; // array for solutions
    errno = 0;
    enum sol_out quantity_of_solutions = solve_quad(a, b, c, &solutions[0], &solutions[1]);
    if (quantity_of_solutions == SOL_ERR)
    {
        printf("%s", get_err_codes(errno));
    }
    
    output(quantity_of_solutions, solutions [0], solutions [1]);
    
    return 0;
}

