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
    double a, b, c;
    solver_code result;
    double sol_1, sol_2;
    int errcode;
};

enum TEST_CODES
{
    TEST_ERROR = 0,
    TEST_SUCCESS = 1
};

/*
@brief Function for testing
*/
int test_func (void);

#endif

