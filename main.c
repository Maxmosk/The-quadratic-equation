#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include "solver.h"

int main()
{
    // input and chacking of initial data
    printf("Enter the coefficients of the quadratic equation\n");
    float a=NAN, b=NAN, c=NAN;
    int QoN=0;
    QoN = scanf("%f%f%f", &a, &b, &c);
    if (QoN != 3)
    {
        printf("Incorrect input");
        return 0;
    }
    
    float solutions [2] = {NAN, NAN}; // array for solutions
    errno = 0;
    enum sol_out quantity_of_solutions = solveQuad(a, b, c, &solutions[0], &solutions[1]);
    if (quantity_of_solutions == SOL_ERR)
    {
        printf("%s", get_err_codes(errno));
    }
    
    output(quantity_of_solutions, solutions [0], solutions [1]);
    getchar();
    return 0;
}
