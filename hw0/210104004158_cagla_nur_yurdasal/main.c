/*
 *   This program asks user to enter some fractional numbers and
 *    does arithmetic calculations with those numbers.
 */

#include <stdio.h>
#include "util.h"

int main()
{

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A fractional number: 13/7 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    /* Getting numbers from the user */
    printf("\nEnter the numerator and denominator parts of the first and the second numbers, respectively.\n");

    printf("Numerator of 1. number: ");
    scanf("%d", &num1);
    printf("Denominator of 1. number: ");
    scanf("%d", &den1);

    printf("Numerator of 2. number:");
    scanf("%d", &num2);
    printf("Denominator of 2. number: ");
    scanf("%d", &den2);

    /* Displaying the numbers entered by the user */
    printf("\nFirst number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    /* Doing calculations */
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    printf("\nAddition: ");
    fraction_print(num3, den3);
    printf("\n");

    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    printf("Subtraction: ");
    fraction_print(num3, den3);
    printf("\n");

    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    printf("Multiplication: ");
    fraction_print(num3, den3);
    printf("\n");

    fraction_div(num1, den1, num2, den2, &num3, &den3);
    printf("Division: ");
    fraction_print(num3, den3);
    printf("\n");

    return (0);
}
