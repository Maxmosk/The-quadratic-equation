#include <stdio.h>
#include <math.h>
#define accuracy 0.001

void output(int QoS, float sol_1, float sol_2);

int decision(float a, float b, float c, float sol[2]);

int main()
{
    printf("Enter the coefficients of the quadratic equation\n");
    float a, b, c;
    scanf("%f%f%f", &a, &b, &c);
    float solutions [2];
    int quantity_of_solutions = decision(a, b, c, solutions);
    output(quantity_of_solutions, solutions [0], solutions [1]);
    getchar();
    return 0;
}

void output(int QoS, float sol_1, float sol_2)
{
    if (QoS == 0)
        printf("No solutions ");
    else if (QoS == 1)
        printf("%f", sol_1);
    else if (QoS == 2)
    {
        printf("%f\n%f", sol_1, sol_2);
    }
}

int decision(float a, float b, float c, float *sol)
{
    float D = b*b - 4*a*c;
    if (D < 0)
        return 0;
    else if (abs(D) < accuracy)
    {
        sol[0] = -b / (2*a);
        return 1;
    }
    else
    {
        sol[0] = (-b + sqrtf(D)) / (2*a);
        sol[1] = (-b - sqrtf(D)) / (2*a);
        return 2;
    }
}
