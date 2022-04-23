/*
 *	This program lets user to choose an operation from
 *	the menu and does necessary calculations and drawings.
 *  In op1, it gets inputs for the equation and saves them
 *  into a .txt file, in op2 it reads saved values from the
 *  .txt file and draws its' graph and in op3, it draws the
 *  same graph without numbers and colors in an another .txt
 *  file. By using op4, user exits the program.
 *
 *  Assignment #4 submission by Çağla Nur Yurdasal
 */
#include <stdio.h>

void write_to_file(int a, int b, int c);
int isAxisX(int y_val);
int isAxisY(int x_val);
int isPoint(int x_val, int y_val, int a, int b, int c);
int isNumberX(int x_val, int y_val);
int isNumberY(int x_val, int y_val);
int countDigits(int val);
void print_backspace(int val);
void cyan()
{
	printf("\033[1;36m");
}
void purple()
{
	printf("\033[1;35m");
}
void reset()
{
	printf("\033[0m");
}
int main(void)
{
	// part0
	int loop_check = 1;
	int selected_operation;
	int a, b, c;
	int x = -50;
	int y = 15;
	int point;
	FILE *fp;

	while (loop_check == 1)
	{
		printf("\nSelect an operation:\n");
		printf("1 -> Enter coefficients.\n");
		printf("2 -> Draw the graph.\n");
		printf("3 -> Print the graph into a .txt file.\n");
		printf("4 -> Exit.\n");
		scanf("%d", &selected_operation);

		switch (selected_operation)
		{
		case 1: // getting a, b, c values for the equation and writing to .txt file
			printf("Please enter coefficients for the following equation: x = a * (y*y) + b*y + c\n");
			printf("a: ");
			scanf("%d", &a);
			printf("b: ");
			scanf("%d", &b);
			printf("c: ");
			scanf("%d", &c);
			write_to_file(a, b, c);

			printf("\ncoefficients.txt file has been created.\n");
			break;
		case 2: // drawing the graph based on the saved values in the txt file

			fp = fopen("coefficients.txt", "r");
			if (fp == NULL)
			{
				printf("Error while opening the file: .txt file does not exist.");
			}
			else
			{
				fscanf(fp, "%d\n", &a);
				fscanf(fp, "%d\n", &b);
				fscanf(fp, "%d\n", &c);
				fclose(fp);
				printf("Coefficients has been read from coefficients.txt file.\n");
				printf("Printing the graph of x = %d*(y*y) + %d*y + %d\n", a, b, c);

				for (int i = 0; i < 54; i++)
				{
					printf(" ");
				}
				printf("^\n");

				for (y = 15; y >= -15; y--)
				{
					printf("    ");
					for (x = -50; x <= 50; x++)
					{

						if (x == -50 && y == 0)
						{
							printf("\b<");
						}
						if (isNumberX(x, y) == 1)
						{
							if (isPoint(x, y, a, b, c) == 0)
							{
								print_backspace(countDigits(x));
								cyan();
								printf("%d", x);
								reset();
							}
						}
						if (isNumberY(x, y) == 1)
						{
							if (isPoint(x, y, a, b, c) == 0)
							{
								print_backspace(countDigits(y));
								cyan();
								printf("%d", y);
								reset();
							}
						}

						if (x == 50 && y == 0)
						{
							printf("\b>");
						}
						char pin = ' ';
						if (isAxisX(y) == 1)
						{
							pin = '-';
						}
						if (isAxisY(x) == 1)
						{
							pin = '|';
						}
						if (isPoint(x, y, a, b, c) == 1)
						{

							pin = '#';
						}

						if (pin == '#')
						{
							purple();
							printf("%c", pin);
						}
						else
						{
							printf("%c", pin);
						}
						reset();
					}
					printf("\n");
				}
			}
			break;
		case 3:

			fp = fopen("coefficients.txt", "r");
			if (fp == NULL)
			{
				printf("Error while opening the file: .txt file does not exist.");
			}
			else
			{
				fscanf(fp, "%d\n", &a);
				fscanf(fp, "%d\n", &b);
				fscanf(fp, "%d\n", &c);
				fclose(fp);
				printf("Coefficients has been read from coefficients.txt file.\n");
				printf("Printing the graph of x = %d*(y*y) + %d*y + %d\n", a, b, c);

				fp = fopen("graph.txt", "w");
				for (int i = 0; i <= 50; i++)
				{
					fprintf(fp, "%s", " ");
				}
				fprintf(fp, "%c\n", '^');

				for (y = 15; y >= -15; y--)
				{
					fprintf(fp, "%s", " ");
					for (x = -50; x <= 50; x++)
					{
						char pin = ' ';
						if (isAxisX(y) == 1)
						{
							pin = '-';
						}
						if (isAxisY(x) == 1)
						{
							pin = '|';
						}
						if (isPoint(x, y, a, b, c) == 1)
						{
							pin = '#';
						}
						fprintf(fp, "%c", pin);
						if (x == 50 && y == 0)
						{
							fprintf(fp, "%c", '>');
						}
					}
					fprintf(fp, "%c", '\n');
				}
			}
			fclose(fp);
			break;
		case 4:
			printf("Goodbye!\n");
			loop_check = -1;
			break;
		default:
			printf("Invalid entry. Please enter only 1-4 from the menu.\n");
			break;
		}
	}
}

int isAxisX(int y_val)
{
	if (y_val == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int isAxisY(int x_val)
{
	if (x_val == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int isPoint(int x_val, int y_val, int a, int b, int c)
{
	if (x_val == a * (y_val * y_val) + b * y_val + c)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void print_backspace(int val)
{
	for (int i = 0; i < val; i++)
	{
		printf("\b");
	}
}
int countDigits(int val)
{
	int val_abs = val;
	if (val_abs < 0)
	{
		val_abs *= -1;
	}

	int digits = 0;
	int temp = val_abs;
	while (temp > 0)
	{
		temp /= 10;
		digits++;
	}
	if (val <= 0)
	{
		digits++;
	}

	return digits;
}
int isNumberX(int x_val, int y_val)
{
	if (y_val == -1)
	{
		if (x_val % 10 == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
int isNumberY(int x_val, int y_val)
{
	if (x_val == -1)
	{
		if (y_val % 5 == 0 && y_val != 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
void write_to_file(int a, int b, int c)
{
	FILE *fp;
	fp = fopen("coefficients.txt", "w");

	fprintf(fp, "%d\n%d\n%d\n", a, b, c);
	fclose(fp);
}
