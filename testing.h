/*
@file Designed for testing the solve_quad function
*/

#ifndef TESTING_H
#define TESTING_H

/*
@brief The struct of data for testing of solver
@param a, b, c is input of solve_quad
@param result is return of solve_quad
@param sol is array for solutios of quad
@param errcode is error code
*/
struct sol_testing_data
{
    float a, b, c;
    enum sol_out result;
    float sol_1, sol_2;
    int errcode;
};

/*
@brief Function for testing
@detailed This function calls the function under test with the passed data and outputs information about the error if there is one
@param examp is structure with sample input and output
*/
static void test_of_sol(struct sol_testing_data examp);

/*
@brief Function for testing
*/
int test_func();

#endif
