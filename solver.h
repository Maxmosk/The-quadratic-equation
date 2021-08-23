#ifndef SOLVER_H
#define SOLVER_H
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
@note If the number of solutions is infinite, it returns -1
@noet EDOM is error domain
@note EFAULT is error of bad adress 
@note ERANGE is error of result out of range
*/
int solveQuad(float a, float b, float c, float sol[2]);

/*
@brief This function checks whether the number is zero
@param nmb is the number being compared
@return True if the number is zero, false in other cases
@note Any number less than the ACCURACY is considered zero
*/
int isZero(float nmb);

/*
@brief This function return description of error
@param e_no is value of errno
@return Text string with description of error
*/
char* get_err_codes(int e_no);

#endif

