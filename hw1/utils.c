#include <stdio.h>
#include "utils.h"

int find_divisible(int x, int y, int z)
{
	int f_i;
	int check = 0; // test variable to check whether there is an integer can be divided by z
	for (int i = x + 1; i < y; i++)
	{
		if (i % z == 0)
		{
			f_i = i;
			check = 1;
			break;
		}
	}
	if (!check)
	{
		return (-1);
	}
	else
	{
		return (f_i);
	}
}

int find_nth_divisible(int n, int f_i, int z)
{
	int counter = 0; // counter to count how many integers have passed since first integer

	for (int i = f_i + 1; counter <= n; i++)
	{
		if (i % z == 0)
		{
			counter++;
			if (counter == n)
			{
				return (i);
			}
		}
	}
}

int validate_identity_number(char identity_number[])
{
	int int_id[11];

	// checking whether the array has 11 characters
	int i = 0;
	while (identity_number[i] != '\0')
	{
		i++;
	}
	if (i != 11)
	{
		printf("Given number has not 11 chars\n");
		return (0);
	}

	// checking whether the target index is a digit
	for (int i = 0; i < 11; i++)
	{
		if (identity_number[i] < 58 && identity_number[i] > 47)
		{
			int_id[i] = identity_number[i] - '0'; /* substracting ASCII value of char 0
												   from the target char element in order to
												   get the int value of that target element */
		}
		else
		{
			printf("%d. digit is not a digit\n", i + 1);
			return (0);
		}
	}

	// checking whether the first digit is 0
	if (int_id[0] == 0)
	{
		printf("First digit is 0\n");
		return (0);
	}

	// checking the value of 10th digit
	int sum_evens = 0;
	int sum_odds = 0;
	int sum_digits = 0;
	int mod_10;

	for (int i = 0; i < 9; i++)
	{
		sum_digits += int_id[i]; // getting the sum of the first 10 digits
		if (i % 2 == 0)
		{
			sum_odds += int_id[i]; // add 1,3,5,7,9th digits together
		}
		else
		{
			sum_evens += int_id[i]; // add 2,4,6,8th digits together
		}
	}
	mod_10 = ((7 * sum_odds) - (sum_evens)) % 10;
	if (mod_10 != int_id[9])
	{
		printf("MOD10 of 7 times sum of odd digits minus sum of even digits\nis not equal to 10th digit\n");
		return (0);
	}

	// checking the 11th digit
	sum_digits += int_id[9]; // adding the 10h digit to the sum of first 10 digits
	if (sum_digits % 10 != int_id[10])
	{
		printf("MOD 10 of sum of first 10 digits isn't equal to the 11th digit\n");
		return (0);
	}
	return 1;
}

int create_customer(char identity_number[], int password)
{
	FILE *fp; // file pointer

	fp = fopen("customeraccount.txt", "w");

	fprintf(fp, "%s%s%d", identity_number, ",", password); // saving the ID number and the password in the text file

	fclose(fp);
}

int check_login(char identity_number[], int password)
{

	char id_check[11]; // array to compare identity number in txt file with user entry
	int p_check;	   // to compare password with user entry
	FILE *fp;
	fp = fopen("customeraccount.txt", "r");

	fgets(id_check, 12, fp); // reading first 11 chars in txt file

	for (int i = 0; i < 11; i++)
	{
		if (identity_number[i] != id_check[i]) // checking if id number entered by the user is correct
		{
			return (0);
		}
	}

	fseek(fp, 1, SEEK_CUR); // moving file pointer 1 byte to the right to skip the comma
	while (!feof(fp))
	{
		fscanf(fp, "%d", &p_check); // reading password

		if (p_check == password)
		{
			return (1);
		}

		else
		{
			return (0);
		}
	}
	rewind(fp);
	fclose(fp);
}

int withdrawable_amount(float cash_amount)
{
	// Only multiples of 10,20,50 can be withdrawn
	int withdrawable = 0;
	while (cash_amount >= 10) // unable to withdraw if the amount is less than 10
	{
		if (cash_amount >= 50)
		{
			withdrawable += 50;
			cash_amount -= 50;
		}
		else if (cash_amount >= 20)
		{
			withdrawable += 20;
			cash_amount -= 20;
		}
		else
		{
			withdrawable += 10;
			cash_amount -= 10;
		}
	}
	return withdrawable;
}