/*
 * This program has 4 parts: User gets to choose an operation from the menu. If op1
 * is chosen, program prompts user to choose summation or multiplication and work with
 * even or odd numbers. Results are saved in results.txt. If op2 is chosen, program finds prime numbers until the user
 * provided number.  If 3 is chosen, results obtained in op1 is displayed and if op4
 * is chosen, contents of results.txt is getting sorted.
 *
 * Assignment 3 submission by Çağla Nur Yurdasal
 */

#include <stdio.h>
#include <math.h>

int sum(int n1, int n2, int flag);
int multi(int n1, int n2, int flag);
int isprime(int a);
void write_file(int number);
void sort_file();
void print_file();

int main(void)
{
	int selected_operation, operation_flag, type_flag, num1, num2, sum_result, multi_result, n, isprime_result;
    int check = -1;
	printf("Select operation\n 1. Calculate sum/multiplication between two numbers\n"); // op1
	printf(" 2. Calculate prime numbers\n");    // op2
    printf(" 3. Show number sequence in file\n");   // op3
	printf(" 4. Sort number sequence in file\n -----------------------\n"); //op4

	scanf("%d", &selected_operation);

	switch (selected_operation)
	{
	case 1:
        // if user selected op1, summation or multiplication will be done using user entered values
        do{
            printf("Select operation\nPlease enter '0' for sum, '1' for multiplication.\n");
            scanf("%d", &operation_flag);
            printf("Please enter '0' to work on even numbers, '1' to work on od numbers.\n");
            scanf("%d", &type_flag);
            // checking if user entered valid characters for operation selection
            if (operation_flag < 0 || operation_flag > 1 || type_flag < 0 || type_flag > 1)
            {
                printf("You have entered an invalid character.\n");
            }
            else{
                check = 1;
            }
        }while (check == -1);

		printf("Please enter two different numbers:\n");
		printf("Number 1: ");
		scanf("%d", &num1);
		printf("Number 2: ");
		scanf("%d", &num2);

		switch (operation_flag) // checking if multiplication or summation is going to be done
		{
		case 0:
			sum_result = sum(num1, num2, type_flag);
			write_file(sum_result); // writing the result to the results.txt file
			printf("Result is written to the results.txt file.\n");
			break;
		case 1:
			multi_result = multi(num1, num2, type_flag);
			write_file(multi_result);
			printf("Result is written to the results.txt file.\n");
			break;
		}
		break;
	case 2:
        // if user selected op2, numbers until the user entered value will be checked whether they are prime or not
		printf("Please enter an integer: ");
		scanf("%d", &n);
		for (int a = 2; a < n; a++)
		{
			isprime_result = isprime(a);
			if (isprime_result == 0)
			{
				printf("%d is a prime number.\n", a);
			}
			else
			{
				printf("%d is not a prime number, it is divisible by %d.\n", a, isprime_result);
			}
		}
		break;
	case 3:
        // if user selected op3, contents of results.txt will be displayed
		print_file();
		break;
	case 4:
        // if user selected op4, contents of results.txt will be sorted and displayed
		sort_file();
		print_file();
		break;
	}
}

int sum(int n1, int n2, int flag)
{
	int sum = 0;
	for (int i = n1 + 1; i < n2; i++)
	{
		switch (flag)
		{
		case 0:
			if (i % 2 == 0) // process wil be done using only even numbers
			{
				sum += i;
				printf("%d ", i);
				if (i + 2 < n2)
				{
					printf("+ ");
				}
			}
			break;
		case 1:
			if (i % 2 != 0) // process will be done using only odd numbers
			{
				sum += i;
				printf("%d ", i);
				if (i + 2 < n2)
				{
					printf("+ ");
				}
			}
			break;
		}
	}
	printf("= %d\n", sum);

	return sum;
}
int multi(int n1, int n2, int flag)
{
	int multi = 1;
	for (int i = n1 + 1; i < n2; i++)   // only numbers between n1 and n2, exclusively
	{
		switch (flag)
		{
		case 0:
			if (i % 2 == 0)
			{
				multi *= i;
				printf("%d ", i);
				if (i + 2 < n2)
				{
					printf("* ");
				}
			}
			break;
		case 1:
			if (i % 2 != 0)
			{
				multi *= i;
				printf("%d ", i);
				if (i + 2 < n2)
				{
					printf("* ");
				}
			}
			break;
		}
	}
	printf("= %d\n", multi);

	return multi;
}

int isprime(int a)
{
	// flag == 0 : PRIME
	// flag == 1 : NOT PRIME
	int flag = 1;

		while (flag)
		{
			for (int j = 2; j <= sqrt(a); j++)
			{
				if (a % j == 0)
				{
					return (j);
				}
			}

			flag = 0;
			return (flag);
		}

}

void sort_file()
{
	int min1, min2, min3, temp;
	int count = 0;  // number of items saved in results.txt
	int max = 0;    // max value in results.txt
	int temp_max = 0;   // max value in the set of 3 to be calculated in every loop
	int count_three;    // min1,min2 or min3 will be saved only if their values are changed after every loop

	FILE *fp, *fp_temp;
	fp = fopen("results.txt", "r");
	fp_temp = fopen("temp.txt", "a+");

	// find max in results.txt
	while (!feof(fp))
	{
		fscanf(fp, "%d ", &temp);
		if (temp > max)
		{
			max = temp; // greater term in the file overwrites the max value
		}
		count++;
	}

	while (temp_max < max)
	{
        /* In every loop min1, min2, min3 are set to 2147483647, which is the max
         * value that a signed integer can hold to ensure every new set of 3 min1,
         * min2, min3 can enter the loop after previous min1,min2,min3 values are calculated */
		min1 = 2147483647;
		min2 = 2147483647;
		min3 = 2147483647;
		count_three = 0;
		rewind(fp);

		while (!feof(fp))
		{
			fscanf(fp, "%d ", &temp);
            // calculating the min1, min2, min3 values and swapping if necessary
			if (temp_max < temp)
			{
				if (temp < min3)
				{
					count_three++;  // min1 and/or min2 and/or min3 will be changed for certain if temp < min3
					if (temp < min2)
					{
						if (temp < min1)    // temp < min1, so it should be the new min1
						{
							min3 = min2;
							min2 = min1;
							min1 = temp;
						}
						else
						{
							min3 = min2;    // min1 < temp < min2, so it should be the new min2
							min2 = temp;
						}
					}
					else
					{
						min3 = temp;    // min2 < temp < min3 so, it should be the new min3
					}
				}
			}
		}

		switch (count_three)
		{
		case 2:
            // if min1 and min2 values are changed but min3 is not, only min1 and min2 values will be written to sorted file
			fprintf(fp_temp, "%d %d ", min1, min2);
			temp_max = min2;
			break;
		case 1:
            // if min1 is changed but min2 and min3 are not, only min1 will be written to sorted file
			fprintf(fp_temp, "%d ", min1);
			temp_max = min1;
			break;
		default:
            // if all values are changed, they will be written to sorted file as the new min1, min2 and min3
			fprintf(fp_temp, "%d %d %d ", min1, min2, min3);
			temp_max = min3;
			break;
		}
	}
	fclose(fp);
	rewind(fp_temp);

	fp = fopen("results.txt", "w");
	while (!feof(fp_temp))
	{
		fscanf(fp_temp, "%d ", &temp);
		fprintf(fp, "%d ", temp);
	}
	fclose(fp_temp);
	fclose(fp);
	printf("Sorting is complete.\n");
}

void print_file()
{
	int read_value;
	FILE *fPtr = fopen("results.txt", "r");
	printf("Result:\n");
	while (!feof(fPtr))
	{
		fscanf(fPtr, "%d ", &read_value);
		printf("%d ", read_value);
	}
	printf("\n");
	fclose(fPtr);
}
void write_file(int number)
{
	FILE *fPtr;
	fPtr = fopen("results.txt", "a+");
	fprintf(fPtr, "%d ", number);
	fclose(fPtr);
}