#include <stdio.h>
#include <math.h>
int main()
{
    printf("Enter the coefficients of the quadratic equation");
    float a, b, c;
    scanf("%f%f%f", &a, &b, &c);
    float D = b*b - 4*a*c;
    if (D < 0)
        printf("No solutions ");
    else if (D == 0.0)
        printf("%f", -b / (2*a));
    else
    {
        printf("%f", (-b + sqrtf(D)) / (2*a));
        printf("%f", (-b - sqrtf(D)) / (2*a));
    }
    getchar();
    return 0;
}
