#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator)
{
    printf("%d//%d", numerator, denominator);
} /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int *n3, int *d3)
{
    *n3 = n1 * d2 + n2 * d1;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int *n3, int *d3)
{
    *n3 = n1 * d2 - n2 * d1;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int *n3, int *d3)
{
    *n3 = n1 * n2;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int *n3, int *d3)
{
    *n3 = n1 * d2;
    *d3 = n2 * d1;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplifying the given fraction such that they are divided by their GCD */
void fraction_simplify(int *n, int *d)
{

    int gcd = 1;     // the greatest common divisor to be calculated
    int i = 1;       // counter for the loop
    int lower_bound; // loop will iterate until it reaches the lower bound
    int temp;        // temp value to hold the lower bound if numerator or denominator is negative

    /* Checking if numerator and/or denominator is/are negative and deciding the lower bound */

    if (*n < 0 && *d < 0)
    {
        *n *= -1; // getting the absolute value
        *d *= -1;
        if (*n < *d) // deciding the lower bound by checking which part is greater than the other
        {
            lower_bound = *n;
        }
        else
        {
            lower_bound = *d;
        }
    }
    else if (*n < 0 && *d > 0)
    {
        temp = *n * -1; // holding the absolute value to be used
        if (temp < *d)  // deciding the lower bound by checking which part is greater than the other
        {
            lower_bound = temp;
        }
        else
        {
            lower_bound = *d;
        }
    }
    else if (*n > 0 && *d < 0)
    {
        temp = *d * -1; // holding the absolute value to be used
        if (temp < *n)  // deciding the lower bound by checking which part is greater than the other
        {
            lower_bound = temp;
        }
        else
        {
            lower_bound = *n;
        }
    }
    else if (*n > 0 && *d > 0)
    {
        if (*n < *d) // deciding the lower bound by checking which part is greater than the other
        {
            lower_bound = *n;
        }
        else
        {
            lower_bound = *d;
        }
    }

    /* Finding the greatest common divisor */
    while (i <= lower_bound)
    {
        if (*n % i == 0 && *d % i == 0) // checking if both numerator and denominator are divisible by the value of i
        {
            gcd = i;
        }
        i++;
    }

    /* Simplifying the number by dividing both numerator and denominator with the greatest common divisor */
    *n /= gcd;
    *d /= gcd;

} /* end fraction_simplify */
