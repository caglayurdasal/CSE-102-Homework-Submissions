/*
 * CSE102 HW#1 submission by Çağla Nur Yurdasal
 *
 * This program has 3 parts: 1. part finds a divisible in a range given by
 * the user, 2. part validates a T.C identity number and store it in a .txt
 * file along with a password, and the 3. part calculates how much money
 * customer can withdraw if login is successful.
 */

#include <stdio.h>
#include "utils.h"

int main(void)
{

	/*** PART 1: Finding a divisible between two numbers ***/

	int n1, n2, div, n; // first int, second int, divisor and n. divisible
	int f_i;			// first integer between n1 and n2 that can be divided by div
	int n_i;			// n. integer after f_i, if f_i exists
	printf("\n----- PART 1 -----\n");
	printf("Enter the first integer: "); // getting n1 value as the first integer
	scanf("%d", &n1);

	printf("Enter second integer: "); // getting n2 value as the second integer
	scanf("%d", &n2);

	printf("Enter the divisor: "); // getting the div value as the divisor
	scanf("%d", &div);

	f_i = find_divisible(n1, n2, div);
	if (f_i != -1) // looking for the next divisible integers if there is an integer f_i between n1 and n2 that can be divisible by div
	{
		printf("The first integer between %d and %d divided by %d is %d\n", n1, n2, div, f_i);
		printf("Enter the number how many next: ");
		scanf("%d", &n);
		n_i = find_nth_divisible(n, f_i, div);
		if (n_i >= n2)
		{
			n_i = -999;
		}
		if (n_i == -999) // printing error message if desired term is out of range
		{
			printf("No possible to find %dth divisible between %d and %d divided by %d\n", n, n1, n2, div);
		}
		else
		{
			printf("The %d. integer between %d and %d divided by %d is %d\n", n + 1, n1, n2, div, n_i);
		}
	}
	else
	{
		printf("There is not any integer between %d and %d can be divided by %d\n", n1, n2, div);
	}

	/*** PART 2: Validating the given identity number ***/
	int check = 0;
	char identity_number[11]; // identity number to be validated
	int user_password;		  // new password to be set for the account, if identity number is valid

	printf("\n----- PART 2 -----\n");

	while (check == 0)
	{
		printf("Enter identity number: ");
		scanf("%s", identity_number);

		if (validate_identity_number(identity_number) == 0)
		{
			printf("Given ID number is NOT valid.\n");
		}
		else
		{
			printf("Given ID number is valid.\n");
			check = 1;
		}
	}

	printf("Set 4-digit password: ");
	scanf("%d", &user_password);
	while (user_password < 1000 || user_password > 9999)
	{
		printf("Please set a 4-digit password: ");
		scanf("%d", &user_password);
	}
	create_customer(identity_number, user_password); // the password will be saved in a text file

	/*** PART 3: Login and withdrawing money ***/

	/* Checking login credentials */
	printf("\n----- PART 3 -----\n");
	check = 0;
	while (check == 0)
	{
		printf("Enter your 11-digit identity number: ");
		scanf("%s", identity_number);

		printf("Enter your password: ");
		scanf("%d", &user_password);

		if (check_login(identity_number, user_password) == 0)
		{
			printf("Invalid identity number or password.\n");
		}
		else
		{
			printf("Login successful.\n");
			check = 1;
		}
	}

	/* Printing withdrawable amount */

	float c_amount; // cash amount that user wants to withdraw
	int w_amount;	// withdrawable amount from the bank
	printf("Enter your withdraw amount: ");
	scanf("%f", &c_amount);

	w_amount = withdrawable_amount(c_amount);
	printf("Withdrawable amount: %d\n", w_amount);

	return (0);
}
