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
*/
int test_func();

#endif
